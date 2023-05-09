package main
import (
	"fmt"
	"crypto/sha256"
	"crypto/hmac"
	"encoding/hex"
	iu "io/ioutil"
	"strings"
       )

func main() {
/* READ FILE */
	/* GET KEY */
	bs, err := iu.ReadFile("key")
	if err != nil {
		fmt.Println("err: File Read \"key\"")
		return
	}

	key := strings.TrimSpace(string(bs))
	fmt.Println("key >> " + string(key))

	data1 := "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9"
	data2 := "eyJzdWIiOiJtYWJ5dGlvbiIsIm5hbWUiOiJ0dHRlZWUyMzQyMzQyMzQyMzQyMzMyZWVzc3MiLCJpYXQiOjE1MTYyMzkwMjJ9"

	h := hmac.New(sha256.New, []byte(key))

	h.Write([]byte(data1 + "." + data2))

	sha := hex.EncodeToString(h.Sum(nil))



/* VERIFY */
	/* COMPARE */
//	ve := strings.TrimSpace(orig[2])
//
//	fmt.Println(ve == sha)


	/* WRITE FILE */
	

	/* PRINT(DEBUG) */
	fmt.Println("Result sha: " + sha)

}
