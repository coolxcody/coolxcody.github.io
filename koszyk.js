
document.addEventListener('input', function() {
    obliczSume();
});

function obliczSume() {
    let sumaProduktow = 0;

// Iteruj przez wszystkie elementy z klasą "produkt"
    let produkty = document.querySelectorAll('.produkt');
    produkty.forEach(function(produkt) {
        let iloscElement = produkt.querySelector('.iloscProduktu');
        let ilosc = parseInt(iloscElement.value) || 0;

        let cenaElement = produkt.querySelector('.cenaProduktu');
        let cenaText = cenaElement.innerText.replace(' zł', ''); // Usuń 'Cena: ' i ' zł'
        let cena = parseFloat(cenaText.replace(',', '.')) || 0; // Zamień przecinek na kropkę, jeśli istnieje

        let sumaProduktu = ilosc * cena;
        produkt.querySelector('.sumaProduktu').innerText = sumaProduktu.toFixed(2) + ' zł';
        sumaProduktow += sumaProduktu;
    });

    let cenaElementD = document.querySelector('.cenaDostawy');
    let cenaTextD = cenaElementD.innerText.replace('Dostawa: ', '').replace(' zł', '');
    let cenaD = parseFloat(cenaTextD.replace(',', '.')) || 0;

    let sumaCalkowita = sumaProduktow + cenaD;

    document.getElementById('sumaProduktow').innerText = 'Suma Produktów: ' + sumaProduktow.toFixed(2) + ' zł';
    document.getElementById('sumaCalkowita').innerText = 'Suma Całkowita: ' + sumaCalkowita.toFixed(2) + ' zł';
}

// Dodaj obsługę przycisku "Złóż zamówienie"
document.getElementById('zlozZamowienieBtn').addEventListener('click', function() {
    alert('Twoje zamówienie zostało przyjęte. Dziękujemy.');
    resetvalue();
});

function resetvalue() {
    // Zresetuj wartości ilości produktów
    let ilosciProduktow = document.querySelectorAll('.iloscProduktu');
    ilosciProduktow.forEach(function(iloscElement)
    {
        iloscElement.value = '';
    });

    obliczSume();
}