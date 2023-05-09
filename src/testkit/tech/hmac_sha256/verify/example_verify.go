package main
import (
	"fmt"
	"crypto/sha256"
	"crypto/hmac"
	"encoding/base64"
	iu "io/ioutil"
	"bytes"
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

	/* GET ELEMENTS */
	bs, err = iu.ReadFile("input.txt")
	if err != nil {
		fmt.Println("err: File Read \"input.txt\"")
		return
	}

	jwt_token := string(bytes.TrimSpace(bs))

	strindex := []string{"Header","Payload","Verify",}
	orig := make([]string, 3)

	jwt_slice := strings.Split(jwt_token, ".")
	for index, elements := range jwt_slice {
		fmt.Println(strindex[index] + " >> " + elements)
		orig[index] = strings.TrimSpace(elements)
	}

	/* MAKE DIGEST (HMAC-SHA256) */
	hp := (orig[0] + "." + orig[1])
	h := hmac.New(sha256.New, []byte(key))
	h.Write([]byte(strings.TrimSpace(hp)))
	sha := base64.RawURLEncoding.EncodeToString(h.Sum(nil))


/* VERIFY */
	/* COMPARE */
	ve := strings.TrimSpace(orig[2])
	fmt.Println(ve == sha)

	/* WRITE FILE */


}
