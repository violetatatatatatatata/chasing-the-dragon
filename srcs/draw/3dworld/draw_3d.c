/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_3d.c  		   								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aalcaide <aalcaide@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by aalcaide		   #+#	  #+#			  */
/*	 Updated: 2026/02/04 12:05:00 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <ctd.h>

static void	ft_calculate_view_and_projection(t_game *g, t_matrix4f view,
	t_matrix4f projection)
{
	matrix_identity(view);
	matrix_translate(view, g->p.x_pos, g->p.y_pos, 0.0f);
	//matrix_rotate_x(view, ft_deg_to_rad(g->camera.pitch));
	//matrix_rotate_y(view, ft_deg_to_rad(g->camera.yaw));
	ft_projection_matrix_perspective(projection, g);
}

/// @brief Calculates object projection
/// @param mvp 
/// @param obj 
/// @param view 
/// @param projection 
static void	ft_calculate_object_mvp(t_matrix4f mvp, t_object *obj,
	t_matrix4f view, t_matrix4f projection)
{
	t_matrix4f	model;
	t_matrix4f	view_model;

	matrix_identity(model);
	matrix_scale(model, obj->scale.x, obj->scale.y, obj->scale.z);
	matrix_rotate_x(model, ft_deg_to_rad(obj->rotation.x));
	matrix_rotate_y(model, ft_deg_to_rad(obj->rotation.y));
	matrix_rotate_z(model, ft_deg_to_rad(obj->rotation.z));
	matrix_translate(model, obj->position.x, obj->position.y, obj->position.z);
	matrix_multiply(view_model, view, model);
	matrix_multiply(mvp, projection, view_model);
}

void	ft_render_scene(t_game *g)
{
	t_matrix4f	view_matrix;
	t_matrix4f	projection_matrix;
	t_matrix4f	mvp_matrix;
	int			i;

	ft_calculate_view_and_projection(g, view_matrix, projection_matrix);
	i = 0;
	while (i < g->num_objects)
	{
		ft_calculate_object_mvp(mvp_matrix, &g->objects[i],
			view_matrix, projection_matrix);
		ft_draw_object(g, &g->objects[i], mvp_matrix);
		i++;
	}
}

static void	ft_matrix_calculate_mvp(t_matrix4f mvp, t_matrix4f model,
		t_matrix4f view, t_matrix4f projection)
{
	t_matrix4f	view_model;

	matrix_multiply(view_model, view, model);
	matrix_multiply(mvp, projection, view_model);
}

static void	ft_matrix_get_mvp(t_matrix4f mvp_matrix, float model_scale,
		t_game *g)
{
	t_matrix4f	projection_matrix;
	t_matrix4f	view_matrix;
	t_matrix4f	model_matrix;

	matrix_identity(model_matrix);
	matrix_rotate_x(model_matrix, ft_deg_to_rad(-90.0f));
	matrix_translate(model_matrix, 0.0f,
		0.0f, 0.0f);
	matrix_scale(model_matrix, model_scale, model_scale, model_scale);
	matrix_identity(view_matrix);
	matrix_translate(view_matrix,
		g->mlx->width / 4,
		g->mlx->height / 4,
		5.0f);
	matrix_rotate_z(view_matrix, ft_deg_to_rad(0.0f));
	matrix_rotate_x(view_matrix, ft_deg_to_rad(35.264f));
	matrix_rotate_y(view_matrix, ft_deg_to_rad(45.0f));
	matrix_identity(projection_matrix);
	projection_matrix_perspective(projection_matrix);
	ft_matrix_calculate_mvp(mvp_matrix, model_matrix,
		view_matrix, projection_matrix);
}

void	draw_3d(t_game *g)
{

}
