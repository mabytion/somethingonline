package models

type User struct {
	Id	string `json:"id"`
	Passwd	string `json:"passwd"`
}

type JToken struct {
	Token	string	`json:"token"`
}
