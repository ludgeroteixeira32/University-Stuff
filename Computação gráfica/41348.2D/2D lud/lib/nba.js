function RoxoClaro(ctx){


                ctx.beginPath();
                ctx.moveTo(0.505,-0.028);
                ctx.lineTo(0.43,-0.028);
                ctx.quadraticCurveTo(0.39,-0.026,0.39,-0.083);
                ctx.lineTo(0.39,-0.9);
                ctx.quadraticCurveTo(0.395,-0.968,0.423,-0.975);
                ctx.lineTo(0.561,-0.975);       
//boneco   
                ctx.quadraticCurveTo(0.556,-0.968,0.559,-0.88);
                ctx.quadraticCurveTo(0.553,-0.876,0.5549,-0.86);
                ctx.quadraticCurveTo(0.537,-0.805,0.543,-0.793);
                ctx.lineTo(0.54,-0.77);
                ctx.quadraticCurveTo(0.48,-0.7,0.435,-0.568);
                ctx.lineTo(0.424,-0.568);
                ctx.quadraticCurveTo(0.417,-0.539,0.413,-0.52);
                ctx.quadraticCurveTo(0.396,-0.45,0.413,-0.39);
                ctx.lineTo(0.4134,-0.38);
                ctx.lineTo(0.406,-0.38);
                ctx.quadraticCurveTo(0.396,-0.38,0.39,-0.36);
                ctx.quadraticCurveTo(0.389,-0.34,0.39,-0.329);
                ctx.lineTo(0.425,-0.2);
                ctx.quadraticCurveTo(0.435,-0.17,0.465,-0.167);
                ctx.lineTo(0.465,-0.161);
                ctx.quadraticCurveTo(0.488,-0.17,0.488,-0.14);
                ctx.lineTo(0.488,-0.113);
                ctx.quadraticCurveTo(0.483,-0.109,0.483,-0.08);
                ctx.lineTo(0.487,-0.08);
                ctx.quadraticCurveTo(0.487,-0.04,0.505,-0.028)
                ctx.closePath();
                ctx.lineWidth=0.01;
                ctx.strokeStyle="#0959B6";
                ctx.stroke();
                ctx.fillStyle="#0959B6";
                ctx.fill();

 




}

function Red(ctx){


                ctx.beginPath();
                ctx.moveTo(0.53,-0.023);
                ctx.lineTo(0.5675,-0.023);
                ctx.quadraticCurveTo(0.6075,-0.026,0.6075,-0.083);
                ctx.lineTo(0.6075,-0.9);
                ctx.quadraticCurveTo(0.6075,-0.968,0.58,-0.975);
                ctx.quadraticCurveTo(0.59,-0.938,0.578,-0.889);
                ctx.lineTo(0.579,-0.87)
                ctx.lineTo(0.578,-0.87)
                ctx.quadraticCurveTo(0.57,-0.83,0.576,-0.81);
                ctx.quadraticCurveTo(0.58,-0.78,0.57,-0.755);
                ctx.quadraticCurveTo(0.56,-0.67,0.55,-0.65);
                ctx.quadraticCurveTo(0.53,-0.58,0.535,-0.57);
                ctx.quadraticCurveTo(0.535,-0.52,0.53,-0.48);
                ctx.lineTo(0.535,-0.475);
                ctx.lineTo(0.52,-0.38);
                ctx.lineTo(0.516,-0.37);
                ctx.lineTo(0.53,-0.3);
                ctx.lineTo(0.542,-0.27);
                ctx.lineTo(0.548,-0.35);
                ctx.lineTo(0.57,-0.47);
                ctx.lineTo(0.585,-0.47);
                ctx.quadraticCurveTo(0.585,-0.37,0.58,-0.36);
                ctx.lineTo(0.57,-0.28);
                ctx.quadraticCurveTo(0.57,-0.23,0.55,-0.20);
                ctx.lineTo(0.55,-0.195);
                ctx.lineTo(0.53,-0.18);
                ctx.quadraticCurveTo(0.53,-0.18,0.532,-0.17);
                ctx.quadraticCurveTo(0.5405,-0.15,0.541,-0.13);
                ctx.lineTo(0.545,-0.125);
                ctx.lineTo(0.55,-0.10);
                ctx.lineTo(0.548,-0.101);
                ctx.quadraticCurveTo(0.55,-0.05,0.541,-0.04);
                ctx.quadraticCurveTo(0.535,-0.023,0.53,-0.023);
                ctx.closePath();
                ctx.lineWidth=0.001;
                ctx.strokeStyle="#E7004C";
                ctx.stroke();
                ctx.fillStyle="#E7004C";
                ctx.fill();

 




}
function Bola(ctx){
    			ctx.beginPath();
    			ctx.arc(0, 0, 1, 0, 2 * Math.PI);
   				ctx.fillStyle = "white";
    			ctx.fill();
}
function Letras(ctx){


            ctx.font = "900 70px Noto Sans CJK JP Bold";
            ctx.fillStyle = "white";
            ctx.fillText("NBA", 1, 5);



}

function Letra(ctx){

            ctx.beginPath();
            ctx.moveTo(0,0);
            ctx.lineTo(0,0.5);
            ctx.lineTo(0.375,1);
            ctx.lineTo(0.65,0.5);
            ctx.closePath();
            ctx.lineWidth=0.00001;
            ctx.strokeStyle="#FFFFFF";
            ctx.stroke();
            ctx.fillStyle="red";
            ctx.fill();



}
function LetraN(ctx){
                ctx.beginPath();
                ctx.moveTo(0,0);
                ctx.lineTo(0,1);
                ctx.lineTo(0.1,1);
                ctx.lineTo(0.1,0.35);
                ctx.lineTo(0.2,1);
                ctx.lineTo(0.33,1);
                ctx.lineTo(0.33,0);
                ctx.lineTo(0.22,0);
                ctx.lineTo(0.22,0.65);
                ctx.lineTo(0.1,0);
                ctx.fillStyle="white";
                ctx.fill();
}


function LetraB(ctx){
                ctx.beginPath();
                ctx.moveTo(0,0);
                ctx.lineTo(0,1);
                ctx.lineTo(0.15,1);
                ctx.quadraticCurveTo(0.3,1,0.25,0.65);
                ctx.quadraticCurveTo(0.2,0.5,0.18,0.5);
                ctx.quadraticCurveTo(0.26,0.46,0.25,0.25);
                ctx.quadraticCurveTo(0.25,0.07,0.18,0);
                ctx.fillStyle="white";
                ctx.fill();
}

function LetraBinside(ctx){
                ctx.beginPath();
                ctx.moveTo(0,0.5);
                ctx.lineTo(0,1);
                ctx.lineTo(0.15,1);
                ctx.quadraticCurveTo(0.3,1,0.25,0.65);
                ctx.quadraticCurveTo(0.2,0.5,0.18,0.5);
                ctx.fillStyle="#0959B6";
                ctx.fill();
}

function LetraA(ctx){
                ctx.beginPath();
                ctx.moveTo(0.4,0);
                ctx.lineTo(0.3,1);
                ctx.lineTo(0.7,1);
                ctx.lineTo(0.6,0);
                ctx.fillStyle="white";
                ctx.fill();
}
function LetraAinside1(ctx){
                ctx.beginPath();
                ctx.moveTo(0.5,0);
                ctx.lineTo(0.25,1);
                ctx.lineTo(0.75,1);
                ctx.fillStyle="#0959B6";
                ctx.fill();
}

function LetraAinside2(ctx){
                ctx.beginPath();
                ctx.moveTo(0.3,0);
                ctx.lineTo(0.25,1);
                ctx.lineTo(0.75,1);
                ctx.lineTo(0.7,0);
                ctx.fillStyle="#0959B6";
                ctx.fill();
}
function enter(ctx, dx, dy, sx, sy) {       //posiçao  x   y   tamanho x,y
                ctx.save();
                ctx.translate(dx,dy);
                ctx.scale(sx,sy);
                
}
function sair (ctx){
    

                ctx.restore();

}
function main(){


                var ctx = document.getElementById("canvas").getContext("2d");

    
                ctx.save();
                    ctx.translate(10,0);
                    ctx.scale(680,-500);
                    RoxoClaro(ctx);                 
                ctx.restore();

                ctx.save();
                    ctx.translate(10,0);
                    ctx.scale(680,-500);
                    Red(ctx);                   
                ctx.restore();
                ctx.save();
                    ctx.translate(404,250);
                    ctx.scale(25,37);
                    Bola(ctx);                   
                ctx.restore();
// Letra N
                ctx.save();
                    ctx.translate(290,400);
                    ctx.scale(80,60);
                    LetraN(ctx);                   
                ctx.restore();
// Letra B
                ctx.save();
                    ctx.translate(321,400);
                    ctx.scale(100,60);
                    LetraB(ctx);                   
                ctx.restore();
//interior B baixo
                ctx.save();
                    ctx.translate(332,421);
                    ctx.scale(24,30);
                    LetraBinside(ctx);                   
                ctx.restore();
//interior B cima               
                ctx.save();
                    ctx.translate(332,399);
                    ctx.scale(22,26);
                    LetraBinside(ctx);                   
                ctx.restore();

                ctx.save();
                    ctx.translate(328,400);
                    ctx.scale(70,60);
                    LetraA(ctx);                   
                ctx.restore();
//interior A cima 
                ctx.save();
                    ctx.translate(358,408);
                    ctx.scale(10,25);
                    LetraAinside1(ctx);                   
                ctx.restore();
//interior A baixo
                ctx.save();
                    ctx.translate(354,447);
                    ctx.scale(19,22);
                    LetraAinside2(ctx);                   
                ctx.restore()



}