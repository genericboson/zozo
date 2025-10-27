extends Control

@onready var dropDown = $CharacterDropDown

func _ready():
	dropDown.add_item("Choose your character")

func _physics_process(_delta: float) -> void:
	#dropDown.add_item()
	pass
