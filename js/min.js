const array = [2, 5, 6, -7, 12, 15, 0, 3, -8, 9];
let min = array[0];
for (let i = 0; i < array.length; i++) {
    if (min > array[i]) min = array[i];
}
