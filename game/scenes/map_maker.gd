extends Node2D

onready var source_texture = preload("res://assets/tiles/terrainTiles_retina.png")

func _ready():
	var ts = TileSet.new()
	# add_child(ts)
	
	for x in range(10):
		for y in range(4):
			var region = Rect2(x * 128, y * 128, 128, 128)
			var id = x + y * 10
			ts.create_tile(id)
			ts.tile_set_texture(id, source_texture)
			ts.tile_set_region(id, region)
	ResourceSaver.save("res://assets/tiles_terrain.tres", ts)
