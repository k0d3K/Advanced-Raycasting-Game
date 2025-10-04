/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:51:54 by dath              #+#    #+#             */
/*   Updated: 2025/05/06 17:34:45 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# define MLX_INIT_FAIL			"mlx_init failed\n"
# define MLX_WIN_FAIL			"mlx_new_window failed\n"
# define MLX_IMG_FAIL			"Images init failed\n"

# define ERROR_TEXT				"Error\n"

# define ERR_ARGC				"The program needs one and only one argument"
# define ERR_INVALID_SUFFIX		"The program needs as an \
argument as a .cub or .adv format."

/* map parsing */
# define ERR_INVALID_RGB_FMT	"Invalid RGB format: %s"

/* map validation */
# define ERR_MISPLACED_PLAYER	"Player character at an invalid position"
# define ERR_INVALID_LAYOUT		"Invalid map layout"
# define ERR_PLAYER_NOT_FOUND	"Player character not found"
# define ERR_EXIT_NOT_FOUND		"Exit not found"
# define ERR_INVALID_CHAR		"Invalid character"
# define ERR_TOO_MANY_PLAYERS	"Only one player character must be present"
# define ERR_TOO_MANY_EXIT		"Only one exit must be present"
# define ERR_NO_MAP				"No map in the scene"
# define ERR_OPEN				"Cannot open %s"
# define ERR_INCOMPLETE_SCENE	"Incomplete scene"
# define ERR_INVALID_LINE		"Invalid line: %s"
# define ERR_IDENTIFIER			"Unknown identifier: %s"
# define ERR_DOUBLE_ID			"Multiple defintion of identfier %s"
# define ERR_ATLAS_SIZE			"Invalid size for atlas: %s"
# define ERR_POS_OOB			"Impossible de place a entity outside of the\
 map: x=%0.1f y=%0.1f"
# define ERR_POS_TOO_HIGHT		"Impossible de place a entity on one of the\
 highest wall of the map: x=%0.1f y=%0.1f"

/* bitmap loading */
# define ERR_OPEN_FAILED		"Open failed."
# define ERR_READ_FAILED		"Read failed."
# define ERR_INVALID_MAGIC		"Invalid magic."
# define ERR_BMP_TOO_SMALL		"Image too small"
# define ERR_INVALID_SIZE		"Promised size vs actual size mismatch \
or read error."
# define ERR_INVALID_OFFSET		"Invalid data offset."
# define ERR_INVALID_DIB		"Only BITMAPCOREHEADER DIB header is supported."
# define ERR_INVALID_BPP		"Only 24 BPP is supported."
# define ERR_SIZE_OOB			"Image size too big or too small"
# define ERR_INVALID_RATIO		"Image size is invalid"
# define ERR_INVALID_CP			"Color plane value must be 1."

/* misc */
# define ERR_MALLOC				"Malloc failed"
# define ERR_FAILED_TO_LOAD		"Failed to load %s: %s"
# define ERR_PTHREAD_CREATE		"Failed to create rendering thread: %s"
# define CONSOLE_RED			"\033[0;31m"
# define CONSOLE_RESET			"\033[0m"
# define UNICODE_ARROW			"\xe2\x86\x91"

#endif
