// 1. Scrieti un program intr-unul din limbajele de programare Python, C++, Java, C# care:
// a. Defineste o clasa B avand un atribut b de tip intreg si o metoda de tiparire care
//      afiseaza atributul b la iesirea standard.
// b. Defineste o clasa D derivata din B avand un atribut d de tip sir de caractere si de
//      asemenea o metoda de tiparire pe iesirea standard care va afisa atributul b din
//      clasa de baza si atributul d.
// c. Defineste o functie care construieste o lista continand: un obiect o1 de tip B avand
//      b egal cu 8; un obiect o2 de tip D avand b egal cu 5 si d egal cu "D5" un obiect o3
//      de tip B avand b egal cu -3; un obiect o4 de tip D avand b egal cu 9 si d egal cu "D9".
// d. Defineste o functie care primeste o lista cu obiecte de tip B si returneaza o lista
//      doar cu obiectele care satisfac proprietatea: b>6.
// e. Pentru tipul de data lista utilizat în program, scrieti specificatiile operatiilor
//      folosite.

import java.lang.String;
import java.lang.Override;
import java.util.ArrayList;
import java.util.List;

public class Ex1 {
    static class B {
        public int b;

        public B(int b) {
            this.b = b;
        }

        public void print() {
            System.out.println("b = " + b);
        }
    }

    static class D extends B {
        private String d;

        public D(int b, String d) {
            super(b);
            this.d = d;
        }

        @Override
        public void print() {
            System.out.println("b = " + b + " d = " + d);
        }
    }

    public static List<B> buildList() {
        ArrayList<B> objs = new ArrayList<>();

        B o1 = new B(8);
        D o2 = new D(5, "D5");
        B o3 = new B(-3);
        D o4 = new D(9, " D9");

        objs.add(o1);
        objs.add(o2);
        objs.add(o3);
        objs.add(o4);
        return objs;
    }

    public static List<B> objectsWithBGreaterThanSix(List<B> bs) {
        List<B> filtered = new ArrayList<>();

        for (int i = 0; i < bs.size(); i++) {
            if (bs.get(i).b > 6) {
                filtered.add(bs.get(i));
            }
        }

        return filtered;
    }

    /**
     * List.add(l^{io}, e^i): adauga un element in lista
     * 
     * @pre: l - lista cu elemente de tipul lui e, e - element de adaugat
     * @post: l = l U {e} - e o sa fie adaugat in lista e
     */

    /**
     * List.size(l^{i}, dim^{o}): returneaza dimensiunea listei
     * 
     * @pre: l - lista
     * @post: dim va contine dimensiunea listei l = 0, daca l este vida, numar
     *        natural nenul altfel
     */

    public static void main(String[] args) {
        List<B> initialB = buildList();
        System.out.println("Initial B objects...");
        for (B b : initialB) {
            b.print();
        }

        System.out.println("Filtered B objects...");
        List<B> filteredB = objectsWithBGreaterThanSix(initialB);
        for (B b : filteredB) {
            b.print();
        }
    }
}