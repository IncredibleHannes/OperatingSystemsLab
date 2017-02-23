public class SiebDesEratosthenes {
    public static void main(String[] args) {
        int n = 0;
        if(args.length == 1){
            n = Integer.parseInt(args[0]);
        }else{//read from console
            System.out.println("Bis zu welcher oberen Grenze sollen Primzahlen berechnet werden?");
            String input = System.console().readLine();
            n = Integer.parseInt(input);
        }
        SiebDesEratosthenes sde = new SiebDesEratosthenes(n);
    }

    private int n;


    public SiebDesEratosthenes(int n){
        System.out.println("current n: " + n);
        //todo do sth
    }
}