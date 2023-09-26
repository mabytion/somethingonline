package models

type User struct {
	Id	string	`db:"id" json:"id"`
	Passwd	string	`db:"passwd" json:"passwd"`
	Email	string	`db:"email" json:"email"`
}

type User2 struct {
	Id string `db:"id" json:"id"`
}

type RData struct {
	Token	string	`json:"token"`
}
