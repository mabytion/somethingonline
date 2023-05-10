package mabytion

import (
	"crypto/sha256"
	"crypto/hmac"
	"encoding/base64"
	"strings"
       )

const (
	SHA256 = 0
      )

type Key struct {
	key string
}

func SetKey(key string) Key {
	return Key{key:key}
}

func (key_ *Key) Create(data string, mode int) string {
	switch mode {
		case 0: {
			h := hmac.New(sha256.New, []byte(key_.key))
			h.Write([]byte(strings.TrimSpace(data)))

			return base64.RawURLEncoding.EncodeToString(h.Sum(nil))
		}
	}

	return "err"
}
