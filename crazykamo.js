var gStdscr;
var gStdcon;
var gDeck;
var gKamoImg;
var gCursorFocus = -1;

/** Card()
 * Cards are the moveable objects in this game
 * @param pos position on the game board (0-8)
 * @param r rotation of card
 * @param id position on the source image (0-8) */
function Card(pos, r, id) {

    this.pos = pos;
    this.r = r;
    this.id = id;
}

/** createNewDeck() 
 * shuffles the deck of Cards (gDeck) */
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
    
    /* Every created card gets a random id and rotation: */
    gDeck = [new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ,new Card(i++, Math.floor(Math.random() * 4), IDs.pop())
            ];
}

/** drawOutline() 
 * Draw a nice box around a Card
 * @param cardNumber Card.pos of the card we'll outline
 * @param color color of the border */
function drawOutline (cardNumber, color) {
    var x = (cardNumber % 3) * 150;
    var y = Math.floor(cardNumber / 3) * 150;
    gStdcon.strokeStyle = color;
    gStdcon.strokeRect(x, y, 150, 150);
}

/** drawDeck() 
 * Draw all cards to the canvas 
 * @param drawList list of cards to draw 
 *
 * Since I have no idea how to rotate an Image object we'll 
 * rotate the canvas 4 times and blit the relevant cards on 
 * the relevant rotation */
function drawDeck (drawList) {
    var sx, sy, tx, ty;
    for (var r = 0; r < 4; r++) {
        for (var i = drawList.length -1; i >= 0; i--) {
            if (drawList[i].r == r) {
                sx = (drawList[i].id % 3) * 150;
                sy = Math.floor(drawList[i].id / 3) * 150;
                switch(r) {
                case 0:
                    tx = (drawList[i].pos % 3) * 150;
                    ty = Math.floor(drawList[i].pos / 3) * 150;
                    break;
                case 1:
                    tx = Math.floor(drawList[i].pos / 3) * 150;
                    ty = -((drawList[i].pos % 3) +1) * 150;
                    break;
                case 2:
                    tx = -((drawList[i].pos % 3) +1) * 150;
                    ty = -(Math.floor(drawList[i].pos / 3) +1) * 150;
                    break;
                case 3:
                    tx = -(Math.floor(drawList[i].pos / 3) +1) * 150;
                    ty = (drawList[i].pos % 3) * 150;
                    break;
                }
                gStdcon.drawImage(gKamoImg, sx, sy, 150, 150, tx, ty, 150, 150);
            }
        }
        gStdcon.rotate(Math.PI / 2);
    }
    
    /* Draw a grid:
     * We'll use this as a way of highlighting cards later */
    gStdcon.beginPath();
    for (var i = 0; i <= 450; i += 150) {
        gStdcon.moveTo(i, 0);
        gStdcon.lineTo(i, 450);
        gStdcon.moveTo(0, i);
        gStdcon.lineTo(450, i);
    }
    gStdcon.strokeStyle = "grey";
    gStdcon.stroke();

}

/** handleEventClick()
 * Pretty self explanatory, handle mouseclick events
 * @e event */
function handleEventClick(e) {
    var newFocus = Math.floor(e.pageX / 150) + Math.floor(e.pageY / 150) * 3;

    /* Clicking a Card twice will rotate it clockwise: */
    if (gCursorFocus == newFocus) {
        for (var i = gDeck.length -1; i >= 0; i--)
            if (gCursorFocus == gDeck[i].pos) {
                gDeck[i].r = (gDeck[i].r + 5) % 4;
                drawDeck(gDeck);
                gCursorFocus = -1;
                break;
            }

    /* If no Card is selected: Select it: */
    } else if (gCursorFocus == -1) {
        drawOutline(newFocus, "black");
        gCursorFocus = newFocus;

    /* If a Card is already selected, swap them: */
    } else {
        for (var i = gDeck.length -1 ; i >= 0 ; i--) {
            if (gCursorFocus == gDeck[i].pos)
                var cardPos1 = i;
            else if (newFocus == gDeck[i].pos)
                var cardPos2 = i;
        }
        var tmp = gDeck[cardPos1].pos;
        gDeck[cardPos1].pos = gDeck[cardPos2].pos
        gDeck[cardPos2].pos = tmp;
        drawDeck(gDeck);
        gCursorFocus = -1;
    }
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
        drawDeck(gDeck);
     }

}

