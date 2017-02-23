package main.java;

import java.util.*;

public class SiebDesEratosthenes {

    private int n;

    public static void main(String[] args) {
        int n = 0;
        if(args.length == 1) {
            n = Integer.parseInt(args[0]);
        } else {
            //read from console
            System.out.println("Bis zu welcher oberen Grenze sollen Primzahlen berechnet werden?");
            Scanner scanner = new Scanner(System.in);
            n = Integer.parseInt(scanner.next());
        }
        SiebDesEratosthenes sde = new SiebDesEratosthenes(n);
    }



    public SiebDesEratosthenes(int n) {
        System.out.println("current n: " + n);

        Worker test = new Worker(n, 2);
        test.run();
        for(int i = 2; i <= n; i++){
            test.values.add(i);
        }
        test.notify();
    }



    private class Worker implements Runnable{
        private Worker child;
        private int n;
        private int prime;
        Pipeline values;
        private boolean stopped = false;


        Worker(int n, int prime){
            this.n = n;
            this.prime = prime;
            values = new Pipeline(this);
        }


        @Override
        public synchronized void run() {
            System.out.println("run entered");
            while(!stopped){
                try {
                    System.out.println("start waiting");
                    this.wait();
                    System.out.println("end Waiting");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                while(!values.isEmpty()){
                    this.checkValue();
                }
            }

            System.out.println("run stopped");

        }

        private void checkValue() {
            int k =values.getNext();
            if(k <= n ) {

                if (k % prime != 0) {
                    if (child == null && (Math.pow(k, 2) < n)) {
                        child = new Worker(n, k);
                    } else {
                        child.values.add(k);
                    }
                }
            }else{
                this.end();
            }
        }

        void end(){
            System.out.println( prime + ", ");
            if(child != null){
                child.end();
            }
            this.stopped = true;
            this.notify();
        }

    }

    private class Pipeline{
        private ArrayDeque<Integer> elements = new ArrayDeque<Integer>();
        private Worker owner;

        Pipeline(Worker _owner){
            this.owner = _owner;
        }
        int getNext(){
         return elements.pop();
        }

        void add(int newVal){
            elements.push(newVal);
            owner.notify();
        }

        boolean isEmpty(){
            return elements.isEmpty();
        }

    }

}