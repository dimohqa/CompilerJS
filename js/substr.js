const sub = "123";
let check = false;
const str = "asvgwr123wqf";
for (let i = 0; i < str.length; i++) {
    let k = 0;
    if (str[i] === sub[0]) {
        let j = i;
        while (str[j] === sub[k]) {
            j++;
            k++;
        }
    }
    if (k === sub.length) {
        check = true;
        break;
    }
}