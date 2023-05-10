package mabytion

import (
	"encoding/json"
       )

type JWT struct {
	header Header
	payload Payload

}

type Header struct {
	Alg string `json:"alg"`
	Typ string `json:"typ"`
}

type Payload struct {
	Iss string 	`json:"iss""`
	User string	`json:"user"`
	Token string	`json:"token"`
	Exp string	`json:"exp"`
	Iat string	`json:"iat"`
}

func Start() JWT {
	var jwt_ JWT

	return jwt_
}

func (jwt_ *JWT) SetHeader(alg, typ string) {
	jwt_.header.Alg = alg
	jwt_.header.Typ = typ
}

func (jwt_ *JWT) SetPayload(iss, user, token, exp, iat string) {
	jwt_.payload.Iss = iss
	jwt_.payload.User = user
	jwt_.payload.Token = token
	jwt_.payload.Exp = exp
	jwt_.payload.Iat = iat
}

func (jwt_ *JWT) CreateTokenString(key string) string {
	jhead, _ := json.Marshal(jwt_.header)
	jpayload, _ := json.Marshal(jwt_.payload)

	data := Base64Encode(string(jhead)) + "." + Base64Encode(string(jpayload))

	sec := SetKey(key)

	return (data + "." + sec.Create(data, 0))
}
