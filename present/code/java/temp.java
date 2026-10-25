public class temp {
    public static void main(String[] args) {
        try {
            throw new RuntimeException();
        }catch(RuntimeException e){
            System.out.println(e.getMessage());
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
}