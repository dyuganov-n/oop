public class Main {
    public static void main(String[] args){
        try{
            MorseCode morseCode = new MorseCode();
            morseCode.run();
        }
        catch(Throwable e){
            System.err.println("Error somewhere in program: " + e.getLocalizedMessage());
        }
    }
}
