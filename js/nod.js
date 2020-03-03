let a = 100;
let b = 45;
let t;
while (b !== 0) {
    t = b;
    b = a % b;
    a = t;
}