package main

import (
	"auth/mappings"
	_ "github.com/go-sql-driver/mysql"
       )

func main() {
	mappings.CreateUrlMappings()
	mappings.Router.Run(":8081")
}
