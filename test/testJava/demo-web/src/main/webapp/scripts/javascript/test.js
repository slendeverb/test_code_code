var result = "";
var price = new Array(2576.00, 2999.00, 3898.00, 699.00, 599.00, 699.00);
var product = new Array("iPhone 6 32GB 金色 移动联通电信4G",
    "OPPO R11 全网通 黑色版",
    "Apple iPhone 6s Plus 32GB 金色 移动联通电信4G手机",
    "小米 红米手机4X 全网通版 2GB内存 16GB 香槟金",
    "小米 红米手机4A 全网通版 2GB内存 16GB 玫瑰金",
    "小米 红米4X 全网通版 2GB内存 16GB 樱花粉");
var isSelected = new Array(0, 0, 0, 0, 0, 0);

function clearAll() {
    isSelected = [0, 0, 0, 0, 0, 0];
    myForm.sp0.checked = false;
    myForm.sp1.checked = false;
    myForm.sp2.checked = false;
    myForm.sp3.checked = false;
    myForm.sp4.checked = false;
    myForm.sp5.checked = false;
}

function checkOut() {
    var total = 0;
    var count = 0;
    for (var i = 0; i < isSelected.length; i++) {
        count += isSelected[i];
    }
    for (var i = 0; i < price.length; i++) {
        total += price[i] * isSelected[i];
    }
    alert("您所选购的" + count + "件, 产品总价=" + total + "\n" + "请去支付!");
}

function shoppingCart() {
    var selectList = "";
    for (var j = 0; j < product.length; j++) {
        if (isSelected[j]) {
            selectList += (j + 1) + "-" + product[j] + ", 价值=" + price[j] + "\n";
        }
    }
    var info = (selectList == "") ? "您的购物车为空, 请选购!" : selectList;
    alert(info);
}

function checkSelect(number) {
    var temp;
    switch (number) {
        case 0:
            temp = myForm.sp0.checked;
            break;
        case 1:
            temp = myForm.sp1.checked;
            break;
        case 2:
            temp = myForm.sp2.checked;
            break;
        case 3:
            temp = myForm.sp3.checked;
            break;
        case 4:
            temp = myForm.sp4.checked;
            break;
        default:
            temp = myForm.sp5.checked;
            break;
    }
    isSelected[number] = (temp) ? 1 : 0;
}