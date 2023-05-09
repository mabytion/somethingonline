package main

import (
	"encoding/base64"
	"fmt"
       )

func main() {
	data := "{\"alg\":\"HS256\",\"typ\":\"JWT\"}"
	stdenc := base64.StdEncoding.EncodeToString([]byte(data))
	fmt.Println("std enc >> " + stdenc)

	stddec, _ := base64.StdEncoding.DecodeString(stdenc)
	fmt.Println("std dec >> " + string(stddec))

	urlenc := base64.URLEncoding.EncodeToString([]byte(data))
	fmt.Println("url enc >> " + urlenc)
	urldec, _ := base64.URLEncoding.DecodeString(urlenc)

	fmt.Println("url dec: >> " + string(urldec))
}
