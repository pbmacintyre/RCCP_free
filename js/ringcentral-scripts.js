/**
 * Copyright (C) 2018 RingCentral Inc.
 *
 */ 
function isNumberKey(evt){
    var charCode = (evt.which) ? evt.which : event.keyCode
    if (charCode > 31 && (charCode < 48 || charCode > 57))
        return false;
            return true;
}

function reveal_it() {
	var x = document.getElementById("myClientSecret");
    var y = document.getElementById("myRCPassword");    
	if (x.type === "password") {
	  x.type = "text";
	} 
	if (y.type === "password") {
		y.type = "text";
	} 
}

function hide_it() {
	var x = document.getElementById("myClientSecret");
    var y = document.getElementById("myRCPassword");    
	if (x.type === "text") {	  
	  x.type = "password";
	}
	if (y.type === "text") {
	    y.type = "password";
	}
}