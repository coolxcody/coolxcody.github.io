/* Open */
function openNav() {
    document.getElementById("myNav").style.width = "100%";
}

/* Close */
function closeNav() {
    document.getElementById("myNav").style.width = "0%";
}
//----------------------------------------------------------------
window.onscroll = function() {scrollFunction()};
function scrollFunction() {
    if (document.body.scrollTop > 30|| document.documentElement.scrollTop > 30)
    {
        document.getElementById("header").style.fontSize = "60px";
        document.getElementById("header").style.letterSpacing = "10px";
    }
    else 
    {
        document.getElementById("header").style.fontSize = "125px";
        document.getElementById("header").style.letterSpacing = "-13px";
    }
}
//----------------------------------------------------------------
    function openForm() {
    document.getElementById("myForm").style.display = "block";
}

    function closeForm() {
    document.getElementById("myForm").style.display = "none";
}

    function submitForm(event) {
        event.preventDefault();

        document.getElementsByName("e-mail")[0].value = "";

        alert("Dziękujemy za zapisanie się do naszego newslettera!");

        closeForm();
    }
//----------------------------------------------------------------
var slideIndex = 1;
showDivs(slideIndex);

function plusDivs(n) {
    showDivs(slideIndex += n);
}

function showDivs(n) {
    var i;
    var x = document.getElementsByClassName("slides");
    if (n > x.length) {
        slideIndex = 1
    }
    if (n < 1) {
        slideIndex = x.length
    }
    ;
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    x[slideIndex - 1].style.display = "block";
}
//----------------------------------------------------------------
var j = 0;
var txt = 'SPRAWDŹ NASZE PROMOCJE!';
var speed = 80;

window.onload = function() {
    typeWriter();
};

function typeWriter() {

    if (j < txt.length) {
        document.getElementById("demo").innerHTML += txt.charAt(j);
        j++;
        setTimeout(typeWriter, speed);
    }
}
//----------------------------------------------------------------

function Form(event) {
    event.preventDefault();

    document.getElementsByName("uname")[0].value = "";
    document.getElementsByName("message")[0].value = "";

    alert("Dziękujemy za kontakt! Odezwiemy się tak szybko jak to będzie możliwe.");
}

//----------------------------------------------------------------

function Form2(event) {
    event.preventDefault();

    document.getElementsByName("uname")[0].value = "";
    document.getElementsByName("message")[0].value = "";
    document.getElementsByName("powod6")[0].value = "";
    var checkboxes = document.querySelectorAll('input[type="checkbox"]');
    checkboxes.forEach(function(checkbox) {
        checkbox.checked = false;
    });

    alert("Przykro nam, że zwracasz zamówienie. Środki zostaną zwrócone na twoje konto bankowe do pięciu dni roboczych.");
}