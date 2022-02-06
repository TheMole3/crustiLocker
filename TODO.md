I loopen där man checkar transactions i typ några minuter, slå av och på lampan efter varje transaction istället... Tror det funkar bättre





Fortsätt med nordigen grejer

Man måste fixa hela requsitionen och end user agreementet när det har gått ut...
Så lös det...

Kanske man ska lyssna efter status 400 och automatiskt skicka länk för att lösa det

Sen behövs det storage också, dels för config grejer, bättre att ha det där än på github liksom, samt att man kommer behöva ändra requsition id och sånt
Man måste också spara tidigare transactions så att vi inte ger folk crusties så fort de trycker på knappen.

Sen börjar det bli dags att koppla ihop allting tror jag, det gick ju förvånandsvärt bra, jag börjar fatta c++

StatusCode går inte att läsa från JSONen av någon sjuk anlening, lös det med din pigga hjärna ,tack :)



Starta med att ta bort den nuvarande requsitionen
DELETE https://ob.nordigen.com/api/requisitions/57b10ee0-8792-4b5a-824e-25b3ad7f3298

Skapa sedan en ny requsition
POST https://ob.nordigen.com/api/requisitions/
{  
	"redirect": "https://thumbs.dreamstime.com/b/done-text-green-grungy-vintage-rectangle-stamp-done-text-green-grungy-vintage-stamp-214435444.jpg",
	"reference": "crustiLocker",  
    "enduser_id": "crustiLocker",  
  	"agreements": [] 
}

Response
{
    "id": "5afec6db-4e6e-41f1-acb0-e2c0d4d4914a",
    "created": "2022-02-05T20:44:10.544535Z",
    "redirect": "https://thumbs.dreamstime.com/b/done-text-green-grungy-vintage-rectangle-stamp-done-text-green-grungy-vintage-stamp-214435444.jpg",
    "status": "CR",
    "agreements": [],
    "accounts": [],
    "reference": "crustiLocker2",
    "enduser_id": "crusiLocker2"
}

SPARA id!!! resten kan du skita i

Nu kan du göra requsition länkar igen :)


Gammalt REQ UUID 57b10ee0-8792-4b5a-824e-25b3ad7f3298