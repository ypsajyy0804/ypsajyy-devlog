public class Order{

static int a() {
    try {
        return 1;
    }
    finally {
        System.out.print("[a]\n");
    }
}

static int b() {
    try {
        return 1;
    }
    finally {
        return 2;
    }
}

static int c() {
    try {
        throw new RuntimeException("x");
    }
    finally {
        System.out.print("[c]\n");
    }
}

static int d() {
    try {
        return 1;
    }
    finally {
        throw new RuntimeException("y");
    }
}

    public static void main(String[] args) {
        try{
            System.out.println("a() = " + a());
        }catch(RuntimeException e){
            System.out.println("a() catch" + e.getMessage());
        }

        try{
            System.out.println("b() = " + b());
        }catch (RuntimeException e){
            System.out.print("b() catch" + e.getMessage());
        }

        try{
            System.out.println("c() = " + c());
        }catch(RuntimeException e){
            System.out.println("c() catch" + e.getMessage());
        }

        try{
            System.out.println("d() = " + d());
        }catch(RuntimeException e){
            System.out.println("d() catch" + e.getMessage());
        }
    }
}
