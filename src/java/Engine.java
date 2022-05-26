public class Engine {

    static {
        System.loadLibrary("Engine");
    }

    public static void main(String[] args) {
        /*
        Point vertexOne = new Point(0.0, 0.0, 0.0);
        Point vertexTwo = new Point(0.0, 2.0, 0.0);
        Point vertexThree = new Point(2.0, 2.0, 0.0);
        Point vertexFour = new Point(2.0, 0.0, 0.0);

        Line edgeOne = new Line(vertexOne, vertexTwo);
        Line edgeTwo = new Line(vertexTwo, vertexThree);
        Line edgeThree = new Line(vertexThree, vertexOne);

        Plane face = new Plane(vertexOne, vertexTwo, vertexThree, vertexFour);
        System.out.println(face);

        Mesh triangle = new Mesh(face);
         */
        System.out.println(new Engine().nativeTest());
    }

    private native int nativeTest();
}
