# Building 
FROM golang:1.23 as builder
RUN go install github.com/swaggo/swag/cmd/swag@latest
WORKDIR /app
COPY . .
RUN go get github.com/gin-gonic/gin && go get github.com/sirupsen/logrus
RUN go get github.com/swaggo/files && go get github.com/swaggo/gin-swagger
RUN go get go.bug.st/serial && go get github.com/swaggo/swag
RUN swag init
RUN CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o search-restapi-be .

# Creating the final docker image
FROM alpine:latest
RUN apk --no-cache add ca-certificates
WORKDIR /root/
COPY --from=builder /app/search-restapi-be .
#COPY --from=builder /app/docs/* ./docs
CMD ["./search-restapi-be", "5", "0"]
