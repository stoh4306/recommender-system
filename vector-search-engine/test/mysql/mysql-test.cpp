#include <mysql/jdbc.h>

int main() {
    try {
        // Create a driver and connection
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://192.168.0.5:3306", "grida", "MM22mm01#");

        // Connect to the database schema (e.g., test)
        con->setSchema("recommender");

        // Create a new statement
        sql::Statement *stmt;
        stmt = con->createStatement();

        // Execute a query and retrieve the result set
        sql::ResultSet *res;
        res = stmt->executeQuery("SELECT * FROM search_index WHERE name = 'test-index-3'");


        // Loop through the result set and print each row
        while (res->next()) {
            // Retrieve values using column name or index
            int id = res->getInt("id");
            std::string name = res->getString("name");
            std::string path = res->getString("data_path");
            std::cout << "ID: " << id << ", Name: " << name << ", data_path: " << path << std::endl;
        }

        // Insert data to index
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO search_index (name, data_path) VALUES (?, ?)"
        );
        pstmt->setString(1, "test-index-2");
        pstmt->setString(2, "path-2");
        int updateCount = pstmt->executeUpdate();
        std::cout << "Inserted " << updateCount << " row(s) successfully." << std::endl;

        // Cleanup
        delete pstmt;
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }

    return 0;
}
