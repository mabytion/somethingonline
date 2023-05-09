package main
import (
	"os"
	"fmt"
	"crypto/sha256"
	"crypto/hmac"
	"encoding/hex"
	iu "io/ioutil"
       )

func main() {
/* READ FILE */
	/* GET KEY */
	bs, err := iu.ReadFile("key")
	if err != nil {
		fmt.Println("err: File Read \"key\"")
		return
	}

	key := string(bs)
	fmt.Println("key >> " + key)

	/* GET ELEMENTS */
	bs, err = iu.ReadFile("input.txt")
	if err != nil {
		fmt.Println("err: File Read \"input.txt\"")
		return
	}

	fmt_slice := bytes.Split(bs, []byte("."))
	for index, elements := range fmt_slice {
		switch index {
			case 0:
				fmt.Println("Header" + )
			case 1:
			case 2:
		}
	}











	key := "sega"
	data1 := "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9"
	data2 := "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ"
	fmt.Println("data: " + data1 + "." + data2)
	fmt.Println("key: " + key)

	h := hmac.New(sha256.New, []byte(key))

	h.Write([]byte(data1 + "." + data2))

	sha := hex.EncodeToString(h.Sum(nil))

	fmt.Println("Result: " + sha)
}
