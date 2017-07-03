//
// Created by Andrii Lohashchuk on 6/8/17.
//

# include "rt.h"

double    ft_check_min(double t1, double t2)
{
    double temp;

    temp = 0;
    if (t1 != 0 && t2 != 0)
        temp = fmin(t1, t2);
    else if (t1 != 0 || t2 != 0)
        temp = fmax(t1, t2);
    return (temp);
}

double    ft_find_caps(t_cyl *cyl, t_ray r ,double t, t_vec3 p)
{
    t_vec3 q;

    q = vec3_add(r.pos, vec3_mult(r.dir, t));
    if ((vec3_dp(q, q) - vec3_dp(q, p) * 2 + vec3_dp(p, p)) < pow(cyl->rad, 2))
        return (t);
    return (0);
}

double		intersect_plane1(t_cyl *cyl, t_ray r, t_vec3 pos, double t)
{
    double		denom;
    double		t0;
    double		dp;
    t_vec3      normal;
    t_vec3      tmp;

    r.dir = vec3_norm(r.dir);
    normal = vec3_norm(cyl->axis);
    denom = vec3_dp(normal, r.dir);
    tmp = vec3_sub(pos, r.pos);
    dp = vec3_dp(tmp, normal);
    t0 = dp / denom;
    if ((denom > 0.000001 || denom < -0.000001) && dp != 0 && t0 > 0)
    {
        t = t0;
        if (ft_find_caps(cyl, r, t, pos))
            return (t);
    }
    return (0);
}

double    ft_check_between(t_cyl *cyl, t_vec3 pos, t_vec3 dir, double t)
{
    t_vec3 q;

    q = vec3_add(pos, vec3_mult(dir, t));
    if (vec3_dp(cyl->axis, vec3_sub(q, cyl->p1)) > 0 &&
        vec3_dp(cyl->axis, vec3_sub(q, cyl->p2)) < 0)
        return (t);
    return (0);
}

void    ft_caps(t_cyl *cyl, t_ray r, double *t, double  *t_final)
{
    double  t_min_caps;

    cyl->t_low_cap = intersect_plane1(cyl, r, cyl->p1, t[2]);
    cyl->t_top_cap = intersect_plane1(cyl, r, cyl->p2, t[3]);
    t_min_caps = ft_check_min(cyl->t_top_cap, cyl->t_low_cap);
    *t_final = ft_check_min(t_min_caps, *t_final);
    cyl->t_final = *t_final;
}

int			solve_quadric_cut(t_abs solve, double *t_final, t_cyl *cyl, t_ray r)
{
    int		retval;
    double  res;
    double	t[4];

    if (solve.discr < 0)
        retval = 0;
    else
    {
        t[0] = (-solve.b + sqrt(solve.discr)) / (2 * solve.a);
        t[1] = (-solve.b - sqrt(solve.discr)) / (2 * solve.a);
        if (t[0] > t[1])
        {
            t[0] = t[1];
        }
        res = ft_check_between(cyl, r.pos, r.dir, t[0]);
        ft_caps(cyl, r, t, &res);
        if ((res > 0.001) && (res < *t_final))
        {
            *t_final = res;
            retval = 1;
        }
        else
            retval = 0;
    }
    return (retval);
}