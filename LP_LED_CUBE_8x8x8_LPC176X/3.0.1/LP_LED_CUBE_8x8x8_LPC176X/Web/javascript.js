function confirmForm(form, text) {
	if(confirm(text)) {
		form.submit();
	}
}

function toggleTable(id) {
	var element = document.getElementById(id);

	if(element.style.display == "block") {
		element.style.display = "none";
	} else {
		element.style.display = "block";
	}
}

function checkKeyIfNumber(evt) {
    evt = (evt) ? evt : window.event
    var charCode = (evt.which) ? evt.which : evt.keyCode
    if (charCode > 31 && (charCode < 48 || charCode > 57)) {
        return false
    }
    return true
}

function checkTextIP(id) {
	var element = document.getElementById(id);
	if(parseInt(element.value) > 255) {
		element.value = "255"; 
	} else if(parseInt(element.value) < 0) {
		element.value = "0"; 
	}
}