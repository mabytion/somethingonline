package mabytion

import (
	"encoding/base64"
	"strings"
       )

const (
	 URL = true
	 STD = false
      )

func Base64Encode(data string) string {
//	if mode {
		return base64.RawURLEncoding.EncodeToString([]byte(strings.TrimSpace(data)))
//	} else {
//		return base64.RawStdEncoding.EncodeToString([]byte(strings.TrimSpace(data)))
//	}
}

func Base64Decode(data string) string {
//	if mode {
		res, _ := base64.RawURLEncoding.DecodeString(data)
		return string(res)
//	} else { 
//		res, _ := base64.RawStdEncoding.DecodeString(data)
//		return string(res)
//	}
}
