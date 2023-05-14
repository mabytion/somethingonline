package models

type User struct {
	Cid	int64	`db:"cid" json:"cid"`
	Id	string	`db:"id" json:"id"`
	Passwd	string	`db:"passwd" json:"passwd"`
	Email	string	`db:"email" json:"email"`
}

type RData struct {
	Token	string	`json:"token"`
}
