/* Created by Olle Kvarnstrom 
 * Date: 2013-09-08 
 * Kamo.png image made by Sofie Aid */

/* Constants: */
var CARD_SIZE = 150;
var CARDS_PER_ROW = 3;
var CANVAS_WIDTH = CARD_SIZE * CARDS_PER_ROW;
var CANVAS_HEIGHT = CARD_SIZE * CARDS_PER_ROW;
var ROTATIONS = 4;
var KAMO_IMAGE;

/* Mutable things: */
var gCanvasContext;
var gDeck;
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
    var idList = [0, 1, 2, 3, 4, 5, 6, 7, 8];
    for (var i = idList.length, j, tmp; i;) {
        j = Math.floor(Math.random() * i--);
        tmp = idList[i];
        idList[i] = idList[j];
        idList[j] = tmp;
    }
    
    /* Every created card gets a random id and rotation: */
    i = 0;
    gDeck = [new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ,new Card(i++, Math.floor(Math.random() * ROTATIONS), idList.pop())
            ];
}

/** drawOutline() 
 * Draw a nice box around a Card
 * @param cardNumber Card.pos of the card we'll outline
 * @param color color of the border */
function drawOutline (cardNumber, color) {
    var x = (cardNumber % CARDS_PER_ROW) * CARD_SIZE;
    var y = Math.floor(cardNumber / CARDS_PER_ROW) * CARD_SIZE;
    gCanvasContext.strokeStyle = color;
    gCanvasContext.strokeRect(x, y, CARD_SIZE, CARD_SIZE);
}

/** drawDeck() 
 * Draw all cards to the canvas 
 * @param drawList list of cards to draw 
 *
 * Since I have no idea how to rotate an Image object we'll 
 * rotate the canvas 4 times and blit the relevant cards on 
 * the relevant rotation */
function drawDeck (drawList) {
    var sourceX, sourceY, targetX, targetY;
    for (var r = 0; r < ROTATIONS; r++) {
        for (var i = drawList.length -1; i >= 0; i--) {
            if (drawList[i].r == r) {
                sourceX = (drawList[i].id % CARDS_PER_ROW) * CARD_SIZE;
                sourceY = Math.floor(drawList[i].id / CARDS_PER_ROW) * CARD_SIZE;
                switch(r) {
                case 0:
                    targetX = (drawList[i].pos % CARDS_PER_ROW) * CARD_SIZE;
                    targetY = Math.floor(drawList[i].pos / CARDS_PER_ROW)
                      * CARD_SIZE;
                    break;
                case 1:
                    targetX = Math.floor(drawList[i].pos / CARDS_PER_ROW) 
                      * CARD_SIZE;
                    targetY = -((drawList[i].pos % CARDS_PER_ROW) +1) * CARD_SIZE;
                    break;
                case 2:
                    targetX = -((drawList[i].pos % CARDS_PER_ROW) +1) * CARD_SIZE;
                    targetY = -(Math.floor(drawList[i].pos / CARDS_PER_ROW) +1) 
                        * CARD_SIZE;
                    break;
                case 3:
                    targetX = -(Math.floor(drawList[i].pos / CARDS_PER_ROW) +1) 
                        * CARD_SIZE;
                    targetY = (drawList[i].pos % CARDS_PER_ROW) * CARD_SIZE;
                    break;
                }
                gCanvasContext.drawImage(KAMO_IMAGE, 
                                         sourceX, sourceY, CARD_SIZE, CARD_SIZE, 
                                         targetX, targetY, CARD_SIZE, CARD_SIZE);
            }
        }
        gCanvasContext.rotate(Math.PI / 2);
    }
    
    /* Draw a grid:
     * We'll use this as a way of highlighting cards later */
    gCanvasContext.beginPath();
    for (var i = 0; i <= CARDS_PER_ROW; i++) {
        gCanvasContext.moveTo(i * CARD_SIZE, 0);
        gCanvasContext.lineTo(i * CARD_SIZE, CARDS_PER_ROW * CARD_SIZE);
        gCanvasContext.moveTo(0, i * CARD_SIZE);
        gCanvasContext.lineTo(CARDS_PER_ROW * CARD_SIZE, i * CARD_SIZE);
    }
    gCanvasContext.strokeStyle = "grey";
    gCanvasContext.stroke();

}

/** handleEventClick()
 * Pretty self explanatory, handle mouseclick events
 * @e event */
function handleEventClick(e) {
    var newFocus = (Math.floor(e.pageX / CARD_SIZE) 
                    + Math.floor(e.pageY / CARD_SIZE) * CARDS_PER_ROW);

    /* Clicking a Card twice will rotate it clockwise: */
    if (gCursorFocus == newFocus) {
        for (var i = gDeck.length -1; i >= 0; i--)
            if (gCursorFocus == gDeck[i].pos) {
                gDeck[i].r = (gDeck[i].r + ROTATIONS + 1) % ROTATIONS;
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

function initMain(canvasName, imagePath) {
    /* Load image of chameleons: 
     * We MUST wait for the image to load before continuing 
     * otherwise it will just ignore the image for the rest of the session */
    if (arguments.length == 1)
        imagePath = "kamo.png";

    KAMO_IMAGE = new Image();
    KAMO_IMAGE.src = imagePath;
    KAMO_IMAGE.onload = function () {

        /* Create canvas to draw on: */
        var canvas = document.getElementById(canvasName);
        canvas.width = CANVAS_WIDTH
        canvas.height = CANVAS_HEIGHT
        canvas.addEventListener("click", handleEventClick, false);
        canvas.focus();
        gCanvasContext = canvas.getContext("2d");

        /* Init and draw gDeck */
        createNewDeck();
        drawDeck(gDeck);
     }

}

