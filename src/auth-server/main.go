package main

import (
	"auth/controllers"
	"auth/mappings"
	_ "github.com/go-sql-driver/mysql"
       )

func main() {
	controllers.CreateLogger()
	mappings.CreateUrlMappings()
	mappings.Router.Run(":8081")
}
