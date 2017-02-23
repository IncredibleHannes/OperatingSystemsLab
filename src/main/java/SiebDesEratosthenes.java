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
        Worker test = new Worker(n, 2);
        test.start();
        for(int i = 2; i <= n+1; i++){
            test.values.add(i);
        }
        test.parentStopped = true;

    }



    private class Worker extends Thread{
        private Worker child;
        private int n;
        private int prime;
        Pipeline values;
        private boolean parentStopped = false;


        Worker(int n, int prime){
            this.n = n;
            this.prime = prime;
            values = new Pipeline();
        }


        @Override
        public void run() {
            while(!parentStopped || !values.isEmpty()){
                this.checkValue();
            }

            System.out.print( prime + ", ");

            if(child != null){

                child.parentStopped = true;
                synchronized (child.values){
                    child.values.notifyAll();
                }
            }
        }


        private void checkValue() {
            int k =values.getNext(parentStopped);

            if(k <= n && k != -1) {
                if (k % prime != 0) {
                    if (child == null) {
                     //   System.out.println("child spawned: " + k);
                        child = new Worker(n, k);
                        child.start();
                    } else {//(Math.pow(k, 2) < n)
                        child.values.add(k);
                    }
                }
            }else{
                this.end();
            }
        }

        void end(){

            if(child != null){
                synchronized (child.values){
                    child.parentStopped = true;
                    child.values.notifyAll();
                }
            }
        }

    }

    private class Pipeline{
        private ArrayDeque<Integer> elements = new ArrayDeque<>();

        synchronized int getNext(boolean pStopped){
            while(elements.isEmpty() && !pStopped ){
                try {
                    wait();
                }catch (InterruptedException e){
                    e.printStackTrace();
                }
            }
            if(!elements.isEmpty()){
                return elements.poll();
            } else {
              return -1;
            }
        }

        synchronized void add(int newVal){
            elements.add(newVal);
            notifyAll();
        }

        boolean isEmpty(){
            return elements.isEmpty();
        }

    }

}