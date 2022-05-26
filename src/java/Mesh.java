import java.util.ArrayList;
import java.util.Arrays;

public class Mesh {
    public ArrayList<Plane> faces;

    public Mesh(Plane ... faces) {
        this.faces = new ArrayList<Plane>();
        this.faces.addAll(Arrays.asList(faces));
    }

    public void addFace(Plane face) {
        faces.add(face);
    }

    public ArrayList<Plane> getFaces() {
        return faces;
    }
}

class Plane {
    private ArrayList<Line> edges;

    public Plane(Line ... edges) {
        this.edges = new ArrayList<Line>();
        this.edges.addAll(Arrays.asList(edges));
    }

    public Plane(Point ... vertices) {
        edges = new ArrayList<Line>();
        for(int i = 0; i < vertices.length - 1; i++) {
            edges.add(new Line(vertices[i], vertices[i + 1]));
        }
        edges.add(new Line(vertices[vertices.length - 1], vertices[0]));
    }

    public ArrayList<Line> getEdges() {
        return edges;
    }

    public String toString() {
        StringBuilder returnString = new StringBuilder();
        returnString.append("edges: ");
        returnString.append(edges.size());
        returnString.append("\n");
        for(Line edge : edges) {
            returnString.append(edge.toString());
            returnString.append("\n");
        }
        return returnString.toString();
    }
}

class Line {
    private ArrayList<Point> vertices;

    public Line(Point endPointOne, Point endPointTwo) {
        vertices = new ArrayList<Point>();
        vertices.add(endPointOne);
        vertices.add(endPointTwo);
    }

    public ArrayList<Point> getVertices() {
        return vertices;
    }

    public String toString() {
        return vertices.get(0) + " to " + vertices.get(1);
    }
}

class Point {
    private Vector position;

    public Point() {
        position = new Vector();
    }

    public Point(double x, double y, double z) {
        position = new Vector(x, y, z);
    }

    public void setPosition(double x, double y, double z) {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    public Vector getPosition() {
        return position;
    }

    public String toString() {
        return position.toString();
    }
}
