/** CSci-4611 Assignment 6: Harold
 */

#include "sky.h"


Sky::Sky() {
    
}


Sky::~Sky() {
    
}

void Sky::Init(ShaderProgram *stroke3d_shaderprog) {
    stroke3d_shaderprog_ = stroke3d_shaderprog;
}


/// Projects a 2D normalized screen point (e.g., the mouse position in normalized
/// device coordinates) to a 3D point on the "sky", which is really a huge sphere
/// (radius = 1500) that the viewer is inside.  This function should always return
/// true since any screen point can successfully be projected onto the sphere.
/// sky_point is set to the resulting 3D point.  Note, this function only checks
/// to see if the ray passing through the screen point intersects the sphere; it
/// does not check to see if the ray hits the ground or anything else first.
bool Sky::ScreenPtHitsSky(const Matrix4 &view_matrix, const Matrix4 &proj_matrix,
                        const Point2 &normalized_screen_pt, Point3 *sky_point)
{
    // You will need the eye point, this can be 
    // determined from the view matrix as follows:
    Matrix4 camera_matrix = view_matrix.Inverse();
    Point3 eye = camera_matrix.ColumnToPoint3(3);
    
    // TODO: Stitch together your worksheet implementation of this method
    //Origin not same as 0,0,0?? use Point3::Origin similar to line 104/154 in billboard.cc??
    Point3 centerSphere = Point3::Origin();

    Point3 pt3d = GfxMath::ScreenToNearPlane(view_matrix, proj_matrix, normalized_screen_pt);
    Ray ray(eye, (pt3d - eye).ToUnit());
    float t;
    return ray.IntersectSphere(centerSphere, 1500, &t, sky_point);
}




/// Creates a new sky stroke mesh by projecting each vertex of the 2D mesh
/// onto the sky dome and saving the result as a new 3D mesh.
void Sky::AddSkyStroke(const Matrix4 &view_matrix, const Matrix4 &proj_matrix,
                       const Mesh &stroke2d_mesh, const Color &stroke_color)
{
    // TODO: Create a new SkyStroke and add it to the strokes_ array.
    //need to create mesh for skystroke
    Mesh skyMesh(stroke2d_mesh);

    //create new skystroke s
    SkyStroke s;
    s.color = stroke_color;


    //Project the stroke into 3D to lie on the sphere
    std::vector<Point3> verts;

    for (int i = 0; i < skyMesh.num_vertices(); i++) {
        //Point3 skyPoint = Point3(s.mesh.read_vertex_data(i)[0], s.mesh.read_vertex_data(i)[1], s.mesh.read_vertex_data(i)[2]);
        Point3 skyPoint = skyMesh.read_vertex_data(i);
        Point2 pt2d = Point2(skyPoint.x(), skyPoint.y());

        //bool ScreenPtHitsSky takes in (const Matrix4 &view_matrix, const Matrix4 &proj_matrix, const Point2& normalized_screen_pt, Point3* sky_point);
        ScreenPtHitsSky(view_matrix, proj_matrix, pt2d, &skyPoint);
        verts.push_back(skyPoint);
    }

    skyMesh.SetVertices(verts);
    s.mesh = skyMesh;
    strokes_.push_back(s);
}


/// Draws all of the sky strokes
void Sky::Draw(const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {

    // Precompute matrices needed in the shader
    Matrix4 model_matrix; // identity
    Matrix4 modelview_matrix = view_matrix * model_matrix;
    
    // Draw sky meshes
    stroke3d_shaderprog_->UseProgram();
    stroke3d_shaderprog_->SetUniform("modelViewMatrix", modelview_matrix);
    stroke3d_shaderprog_->SetUniform("projectionMatrix", proj_matrix);
    for (int i=0; i<strokes_.size(); i++) {
        stroke3d_shaderprog_->SetUniform("strokeColor", strokes_[i].color);
        strokes_[i].mesh.Draw();
    }
    stroke3d_shaderprog_->StopProgram();
}

