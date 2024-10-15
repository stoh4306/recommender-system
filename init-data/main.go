package main

import (
	"database/sql"
	"encoding/csv"
	"fmt"
	"log"
	"os"

	_ "github.com/go-sql-driver/mysql"
)

func main() {
	dbinfo := "grida:MM22mm01#@tcp(192.168.0.5:3306)/recommder"

	db, err := sql.Open("mysql", dbinfo)

	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// Check if the connection is successful
	err = db.Ping()
	if err != nil {
		log.Fatal("Could not connect to the database:", err)
	}

	fmt.Println("Successfully connected to the database!")

	// Open the CSV file

	//records, err := load_csv_file("project.csv")
	//if err != nil {
	//	return
	//}
	//add_project_data(db, records)
	records, err := load_csv_file("freelancer.csv")
	if err != nil {
		return
	}
	add_freelancer_data(db, records)
}

func load_csv_file(filepath string) ([][]string, error) {
	// Open the CSV file
	file, err := os.Open(filepath)
	if err != nil {
		log.Println(err)
		return nil, err
	}
	defer file.Close()

	// Create a new CSV reader
	reader := csv.NewReader(file)

	// Read all the CSV file content into memory
	records, err := reader.ReadAll()
	if err != nil {
		log.Print(err)
		return make([][]string, 0), err
	}

	// Loop through the records and print them
	for i, record := range records {
		if i == 0 || i == len(records)-1 {
			fmt.Printf("1: %s, 2: %s, 3: %s\n", record[0], record[2], record[4])
		}
	}
	return records, nil
}

func add_project_data(db *sql.DB, records [][]string) error {
	query := "INSERT INTO project (title, description, skills) VALUES (?, ?, ?)"
	for _, record := range records {
		title, descr, skill := record[1], record[3], record[5]
		r, err := db.Exec(query, title, descr, skill)
		if err != nil {
			log.Fatal(err)
		}
		lastInsertID, err := r.LastInsertId()
		if err != nil {
			log.Fatal(err)
		}

		fmt.Printf("New project inserted, ID: %d\n", lastInsertID)
	}
	return nil
}

func add_freelancer_data(db *sql.DB, records [][]string) error {
	query := "INSERT INTO freelancer (name, introduction, skills) VALUES (?, ?, ?)"
	for _, record := range records {
		name, intro, skill := record[0], record[2], record[4]
		r, err := db.Exec(query, name, intro, skill)
		if err != nil {
			log.Fatal(err)
		}
		lastInsertID, err := r.LastInsertId()
		if err != nil {
			log.Fatal(err)
		}

		fmt.Printf("New freelancer inserted, ID: %d\n", lastInsertID)
	}
	return nil
}
