void main(){
    int[] a = {10, 20, 30};
    int[][] b = {{1,2}, {3, 4, 5}};
    char[] c = {'a', 'b', 'c', 'd'};

    IO.println(a[0]);
    a[0] = 100;
    IO.println(a[0]);

    IO.println(a.length);
    IO.println(b.length);

    IO.println(a);
    String aText = Arrays.toString(a);
    IO.println(aText);

    IO.println(b); //выводит закадированное название объекта
    IO.println(Arrays.toString(b)); //выводит закадированные названия объектов внутри объекта b
    IO.println(Arrays.deepToString(b)); //выводит значения объектов внутри объекта b

}
