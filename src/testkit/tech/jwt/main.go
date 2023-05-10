package main

import (
	"fmt"
	tn "mabytion/timenow"
	jtk "mabytion/jwt"
       )

const (
	
      )

func main() {
	id := "mabytion"

	j := jtk.Start()

	j.SetHeader("HS256", "JWT")
	j.SetPayload("Test-Auth", id, "access_token", tn.DatetimeNow(tn.UNIX), tn.DatetimeNow(tn.UNIX))
	
	jstr := j.CreateTokenString("secret")

	fmt.Println(jstr)
}
