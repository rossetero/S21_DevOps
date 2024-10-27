#!/usr/bin/expect -f
spawn ./delivery.sh

expect 
{
	"*fingerprint*" { send -- "yes\r" }
	"*password*" { send -- "1\r" }
}

expect EOF