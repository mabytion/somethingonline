package main

import (
	"fmt"
	tn "mabytion/timenow"
       )


func main() {
	fmt.Println(tn.DatetimeNow(tn.MONGO))
	fmt.Println(tn.DatetimeNow(tn.UNIX))
}
