
public class Test2 {
    public static void main(String[] args) {
        Citizen.country="中国";
        Citizen.f1();
        Citizen c=new Citizen();
        c.name="李华";
        c.f2();

        c.country="中华人民共和国";
        c.f1();
    }

}

class Citizen{
    static String country="China";
    String name="Tom";

    public static void f1(){
        System.out.println(country);
    }

    public void f2(){
        f1();
        System.out.println(country);
        System.out.println(name);
    }
}