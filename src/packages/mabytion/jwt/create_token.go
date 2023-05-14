package mabytion

import (
	"encoding/json"
       )

const (
	ISS = 0
	USER = 1
	TOKEN = 2
	EXP = 3
	IAT = 4
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
	jwt_.SetHeader("HS256", "JWT")
	jwt_.SetPayload("Auth-Test", "", "", "", "")

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

func (jwt_ *JWT) GetPayload(i int) string {
	switch i {
		case ISS:
			return jwt_.payload.Iss
		case USER:
			return jwt_.payload.User
		case TOKEN:
			return jwt_.payload.Token
		case EXP:
			return jwt_.payload.Exp
		case IAT:
			return jwt_.payload.Iat
	}

	return "";
}

func (jwt_ *JWT) SetPayloadIss(iss string) {
	jwt_.payload.Iss = iss
}

func (jwt_ *JWT) SetPayloadUser(user string) {
	jwt_.payload.User = user
}

func (jwt_ *JWT) SetPayloadToken(token string) {
	jwt_.payload.Token = token
}

func (jwt_ *JWT) SetPayloadExp(exp string) {
	jwt_.payload.Exp = exp
}

func (jwt_ *JWT) SetPayloadIat(iat string) {
	jwt_.payload.Iat = iat
}

func (jwt_ *JWT) CreateTokenString(key string) string {
	jhead, _ := json.Marshal(jwt_.header)
	jpayload, _ := json.Marshal(jwt_.payload)

	data := Base64Encode(string(jhead)) + "." + Base64Encode(string(jpayload))

	sec := SetKey(key)

	return (data + "." + sec.Create(data, 0))
}
