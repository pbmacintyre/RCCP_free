
POST /restapi/v1.0/account/~/extension/~/ring-out 

HTTP/1.1 { "from": {"phoneNumber": "+12053320032"}, "to": {"phoneNumber": "+16052160005"}, "playPrompt": true }

// Widget - user on front end is "to"
// they put in their # and triggers the RingOut API.
// Ringout calls Plugin user, who 'answers', then RingOut calls the 
// widget user on the front end who put in the number in the first place.