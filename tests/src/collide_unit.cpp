// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliotheque Lapin

#include		<lapin.h>
#include		<math.h>
#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>

static int		gl_failure = 0;

#define EXPECT_TRUE(expr) do { \
    if (!(expr)) { \
      fprintf(stderr, "[FAIL] %s:%d: expected true: %s\n", __FILE__, __LINE__, #expr); \
      gl_failure += 1; \
    } \
  } while (0)

#define EXPECT_FALSE(expr) do { \
    if (expr) { \
      fprintf(stderr, "[FAIL] %s:%d: expected false: %s\n", __FILE__, __LINE__, #expr); \
      gl_failure += 1; \
    } \
  } while (0)

#define EXPECT_EQ(expected, got) do { \
    long long _expected = static_cast<long long>(expected); \
    long long _got = static_cast<long long>(got); \
    if (_expected != _got) { \
      fprintf(stderr, "[FAIL] %s:%d: expected %lld, got %lld: %s\n", \
		   __FILE__, __LINE__, _expected, _got, #got); \
      gl_failure += 1; \
    } \
  } while (0)

#define EXPECT_STREQ(expected, got) do { \
    const char *_expected = (expected); \
    const char *_got = (got); \
    if ((_expected == NULL && _got != NULL) || \
	(_expected != NULL && _got == NULL) || \
	(_expected != NULL && _got != NULL && strcmp(_expected, _got) != 0)) { \
      fprintf(stderr, "[FAIL] %s:%d: expected \"%s\", got \"%s\"\n", \
		   __FILE__, __LINE__, _expected ? _expected : "(null)", _got ? _got : "(null)"); \
      gl_failure += 1; \
    } \
  } while (0)

static t_bunny_accurate_position pos(double x, double y)
{
  t_bunny_accurate_position p;

  p.x = x;
  p.y = y;
  return (p);
}

static t_bunny_collision dot(const char *name, double x, double y)
{
  t_bunny_collision c;

  memset(&c, 0, sizeof(c));
  c.dot.type = BCT_DOT;
  c.dot.name = name;
  c.dot.coord = pos(x, y);
  return (c);
}

static t_bunny_collision circle(const char *name, double x, double y, double radius)
{
  t_bunny_collision c;

  memset(&c, 0, sizeof(c));
  c.circle.type = BCT_CIRCLE;
  c.circle.name = name;
  c.circle.coord = pos(x, y);
  c.circle.radius = radius;
  return (c);
}

static t_bunny_collision line(const char *name, double ax, double ay, double bx, double by)
{
  t_bunny_collision c;

  memset(&c, 0, sizeof(c));
  c.line.type = BCT_LINE;
  c.line.name = name;
  c.line.coord[0] = pos(ax, ay);
  c.line.coord[1] = pos(bx, by);
  c.line.intermediate_points = 0;
  return (c);
}

static t_bunny_collision triangle(const char *name,
				  double ax, double ay,
				  double bx, double by,
				  double cx, double cy)
{
  t_bunny_collision c;

  memset(&c, 0, sizeof(c));
  c.triangle.type = BCT_TRIANGLE;
  c.triangle.name = name;
  c.triangle.coord[0] = pos(ax, ay);
  c.triangle.coord[1] = pos(bx, by);
  c.triangle.coord[2] = pos(cx, cy);
  return (c);
}

static t_bunny_collision rectangle(const char *name, double x, double y, double w, double h)
{
  t_bunny_collision c;

  memset(&c, 0, sizeof(c));
  c.rectangular.type = BCT_RECTANGLE;
  c.rectangular.name = name;
  c.rectangular.coord[0] = pos(x, y);
  c.rectangular.coord[1] = pos(w, h);
  return (c);
}

static t_bunny_collision quad(const char *name,
			      double ax, double ay,
			      double bx, double by,
			      double cx, double cy,
			      double dx, double dy)
{
  t_bunny_collision c;

  memset(&c, 0, sizeof(c));
  c.quad.type = BCT_QUAD;
  c.quad.name = name;
  c.quad.coord[0] = pos(ax, ay);
  c.quad.coord[1] = pos(bx, by);
  c.quad.coord[2] = pos(cx, cy);
  c.quad.coord[3] = pos(dx, dy);
  return (c);
}

static void		test_line_collisions(void)
{
  t_bunny_collision vertical = line("vertical", 10, 0, 10, 20);
  t_bunny_collision horizontal = line("horizontal", 0, 10, 20, 10);
  t_bunny_collision parallel = line("parallel", 12, 0, 12, 20);
  t_bunny_collision overlap_a = line("overlap_a", 0, 0, 10, 0);
  t_bunny_collision overlap_b = line("overlap_b", 5, 0, 15, 0);
  t_bunny_collision disjoint_a = line("disjoint_a", 0, 0, 10, 0);
  t_bunny_collision disjoint_b = line("disjoint_b", 11, 0, 20, 0);
  t_bunny_collision on_vertical = dot("on_vertical", 10, 8);
  t_bunny_collision off_vertical = dot("off_vertical", 11, 8);
  t_bunny_collision tangent = line("tangent", 5, -10, 5, 10);
  t_bunny_collision unit = circle("unit", 0, 0, 5);

  EXPECT_TRUE(bunny_collide(&vertical, &horizontal));
  EXPECT_FALSE(bunny_collide(&vertical, &parallel));
  EXPECT_TRUE(bunny_collide(&overlap_a, &overlap_b));
  EXPECT_FALSE(bunny_collide(&disjoint_a, &disjoint_b));
  EXPECT_TRUE(bunny_collide(&vertical, &on_vertical));
  EXPECT_FALSE(bunny_collide(&vertical, &off_vertical));
  EXPECT_TRUE(bunny_collide(&tangent, &unit));
}

static void		test_triangle_collisions(void)
{
  t_bunny_collision tri = triangle("tri", 0, 0, 10, 0, 5, 10);
  t_bunny_collision crossing = line("crossing", -1, 5, 11, 5);
  t_bunny_collision outside = line("outside", -1, 11, 11, 11);
  t_bunny_collision inside_circle = circle("inside_circle", 5, 4, 1);
  t_bunny_collision far_circle = circle("far_circle", 20, 20, 1);
  t_bunny_collision huge_circle = circle("huge_circle", 5, 3, 20);

  EXPECT_TRUE(bunny_collide(&tri, &crossing));
  EXPECT_FALSE(bunny_collide(&tri, &outside));
  EXPECT_TRUE(bunny_collide(&tri, &inside_circle));
  EXPECT_TRUE(bunny_collide(&tri, &huge_circle));
  EXPECT_FALSE(bunny_collide(&tri, &far_circle));
}

static void		test_quad_collisions(void)
{
  t_bunny_collision square_a = quad("square_a", 0, 0, 10, 0, 10, 10, 0, 10);
  t_bunny_collision square_b = quad("square_b", 20, 20, 30, 20, 30, 30, 20, 30);
  t_bunny_collision square_c = quad("square_c", 8, 8, 18, 8, 18, 18, 8, 18);
  t_bunny_collision line_through = line("line_through", -2, 5, 12, 5);
  t_bunny_collision line_outside = line("line_outside", -2, 12, 12, 12);
  t_bunny_collision circle_inside = circle("circle_inside", 5, 5, 1);
  t_bunny_collision circle_outside = circle("circle_outside", 15, 5, 2);
  t_bunny_collision tri_inside = triangle("tri_inside", 2, 2, 8, 2, 5, 8);
  t_bunny_collision tri_outside = triangle("tri_outside", 20, 0, 25, 0, 22, 5);

  EXPECT_FALSE(bunny_collide(&square_a, &square_b));
  EXPECT_TRUE(bunny_collide(&square_a, &square_c));
  EXPECT_TRUE(bunny_collide(&square_a, &line_through));
  EXPECT_FALSE(bunny_collide(&square_a, &line_outside));
  EXPECT_TRUE(bunny_collide(&square_a, &circle_inside));
  EXPECT_FALSE(bunny_collide(&square_a, &circle_outside));
  EXPECT_TRUE(bunny_collide(&square_a, &tri_inside));
  EXPECT_FALSE(bunny_collide(&square_a, &tri_outside));
}

static void		test_rectangle_triangle_and_transform(void)
{
  t_bunny_collision rect_inside_tri = rectangle("rect_inside_tri", 4, 2, 2, 2);
  t_bunny_collision tri = triangle("tri", 0, 0, 10, 0, 5, 10);
  t_bunny_collision rect_outside_tri = rectangle("rect_outside_tri", 20, 20, 2, 2);
  t_bunny_collision vertical_rect;
  t_bunny_collision probe = dot("probe", -4, 5);

  EXPECT_TRUE(bunny_collide(&rect_inside_tri, &tri));
  EXPECT_FALSE(bunny_collide(&rect_outside_tri, &tri));

  vertical_rect = rectangle("vertical_rect", 0, 0, 10, 4);
  bunny_turn_collision(&vertical_rect, 90);
  /* A 10x4 rectangle rotated around the origin becomes a 4x10 quad. */
  EXPECT_TRUE(bunny_collide(&vertical_rect, &probe));
}

static void		test_collision_nbr_names(void)
{
  t_bunny_collision a[2];
  t_bunny_collision b[2];
  t_bunny_string_couple couple[4];

  a[0] = circle("A0", 0, 0, 1);
  a[1] = circle("A1", 100, 100, 1);
  b[0] = circle("B0", 100, 100, 1);
  b[1] = circle("B1", 0, 0, 1);
  memset(couple, 0, sizeof(couple));

  EXPECT_EQ(2, bunny_collision_nbr(a, 2, NULL, 0, b, 2, NULL, 0, couple, 4));

  /* This specifically protects against using b[i] instead of b[j]. */
  EXPECT_STREQ("A0", couple[0].first);
  EXPECT_STREQ("B1", couple[0].second);
  EXPECT_STREQ("A1", couple[1].first);
  EXPECT_STREQ("B0", couple[1].second);
}

int			main(void)
{
  test_line_collisions();
  test_triangle_collisions();
  test_quad_collisions();
  test_rectangle_triangle_and_transform();
  test_collision_nbr_names();

  if (gl_failure != 0)
    {
      fprintf(stderr, "collide_unit: %d failure(s)\n", gl_failure);
      return (EXIT_FAILURE);
    }
  fprintf(stdout, "collide_unit: ok\n");
  return (EXIT_SUCCESS);
}
