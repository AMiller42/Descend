function newElement(type, attr) {
    elem = document.createElement(type);

    for (x in attr) {
        elem[x] = attr[x];
    }
    
    return elem
}