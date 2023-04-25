package main

import (
	"fmt"
	"time"
       )

func main() {
	dt := time.Now();

	fmt.Println("Time: ", dt.Format("2006-01-02T15:04:05Z"))

}


