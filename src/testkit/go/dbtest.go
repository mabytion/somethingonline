package main

import (
		"context"
		"encoding/json"
		"fmt"
		"log"
		"os"

		"go.mongodb.org/mongo-driver/bson"
		"go.mongodb.org/mongo-driver/mongo"
		"go.mongodb.org/mongo-driver/mongo/options"
       )

// const uri = "mongodb://user:root@192.168.75.11:27017/?maxPoolSize=20&w=majority"

func main() {
	if err := godotenv.Load(); err != nil {
		log.Println("No .env file found")
	}
	
	uri := os.Getenv("MONGODB_URI")
	
	if uri == "" {
		log.Fatal("You must set your 'MONGODB_URI' environmental variable.")
	}
}
