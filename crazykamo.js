var gStdscr;
var gStdcon;
var gDeck;
var gKamoImg;

function Card (x, y, r, id) {

    /* I've heard this is needed in case you'd ever forget the "new" */
    if (!this instanceof Card)
        return new Card(x, y, r, id);

    this.x = x;   // 0 = Left, 1 = Middle, 2 = Right
    this.y = y;   // 0 = Up,   1 = Middle, 2 = Down
    this.r = r;   // Rotations (e.g. 2 -> rotated 90 degrees 2 times)
    this.id = id; // Which card in the source image to blit from
}

function createNewDeck () {
    /* List of available ids:
     * We'll shuffle it and then pop to get a random id each time
     * Since no one has bothered to implement a shuffle method in js
     * We'll use a Knuth shuffle here */
    var IDs = [0, 1, 2, 3, 4, 5, 6, 7, 8];
    for (var i = IDs.length, j, tmp; i;) {
        j = Math.floor(Math.random() * i--);
        tmp = IDs[i];
        IDs[i] = IDs[j];
        IDs[j] = tmp;
    }
    
    /* Every created card gets a random id: */
    gDeck = [new Card(0, 0, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(0, 1, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(0, 2, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(1, 0, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(1, 1, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(1, 2, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(2, 0, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(2, 1, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(2, 2, Math.floor(Math.random() * 4), IDs.pop())
            ];
}

function drawgDeckFull () {
    /* Draw all cards in gDeck to canvas 
     * Since I have no idea how to rotate an Image object we'll 
     * rotate the canvas 4 times and blit the relevant cards on 
     * the relevant rotation */

    var sx, sy, tx, ty;
    for (var r = 0; r < 4; r++) {
        for (var i = 0; i < gDeck.length; i++) {
            if (gDeck[i].r == r) {
                sx = (gDeck[i].id % 3) * 150;
                sy = Math.floor(gDeck[i].id / 3) * 150;
                switch(r) {
                case 0:
                    tx = gDeck[i].x * 150;
                    ty = gDeck[i].y * 150;
                    break;
                case 1:
                    tx = gDeck[i].y * 150;
                    ty = -(gDeck[i].x +1) * 150;
                    break;
                case 2:
                    tx = -(gDeck[i].x +1) * 150;
                    ty = -(gDeck[i].y +1) * 150;
                    break;
                case 3:
                    tx = -(gDeck[i].y +1) * 150;
                    ty = gDeck[i].x * 150;
                    break;
                }
                gStdcon.drawImage(gKamoImg, sx, sy, 150, 150, tx, ty, 150, 150);
            }
        }
        gStdcon.rotate(Math.PI / 2);
    }
}

function handleEventClick(e) {
// NOT IMPLEMENTED
}

function initMain() {
    /* Load image of chameleons: 
     * We MUST wait for the image to load before continuing 
     * otherwise it will just ignore the image for the rest of the session */
    gKamoImg = new Image();
    gKamoImg.src = "kamo.png";
    gKamoImg.onload = function () {

        /* Create canvas to draw on: */
        gStdscr = document.createElement("canvas");
        gStdscr.id = "crazykamo-canvas";
        gStdscr.width = 450
        gStdscr.height = 450
        gStdscr.addEventListener("click", handleEventClick, false);
        document.body.appendChild(gStdscr);
        gStdcon = gStdscr.getContext("2d");

        /* Init and draw gDeck */
        createNewDeck();
        drawgDeckFull();
     }
}

