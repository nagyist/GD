/**

GDevelop - Tile Map Extension
Copyright (c) 2014-2015 Victor Levasseur (victorlevasseur52@gmail.com)
This project is released under the MIT License.
*/
/**
 * Contributors to the extension:
 * Florian Rival (Minor changes)
 */

#include "GDCpp/ExtensionBase.h"
#include "GDCore/Tools/Version.h"
#include "TileMapObject.h"
#include "RuntimeTileMapObject.h"
#include <iostream>


void DeclareTileMapObjectExtension(gd::PlatformExtension & extension)
{
    extension.SetExtensionInformation("TileMapObject",
                              GD_T("Tile Map Object"),
                              GD_T("Extension allowing to use tile map objects."),
                              "Victor Levasseur and Florian Rival",
                              "Open source (MIT License)");

    gd::ObjectMetadata & obj = extension.AddObject("TileMap",
               GD_T("Tile Map"),
               GD_T("Displays a tile map"),
               "CppPlatform/Extensions/TileMapIcon.png",
               &CreateTileMapObject);

    #if defined(GD_IDE_ONLY)
    obj.SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddCondition("Width",
                   _("Width"),
                   _("Test the width of a Tile Map Object."),
                   GD_T("The width of _PARAM0_ is _PARAM1__PARAM2_"),
                   _("Size"),
                   "res/conditions/scaleWidth24.png",
                   "res/conditions/scaleWidth.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .AddParameter("relationalOperator", GD_T("Sign of the test"))
        .AddParameter("expression", GD_T("Value to test"))
        .MarkAsAdvanced()
        .SetFunctionName("GetWidth").SetManipulatedType("number").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddCondition("Height",
                   _("Height"),
                   _("Test the height of a Tile Map Object."),
                   GD_T("The height of _PARAM0_ is _PARAM1__PARAM2_"),
                   _("Size"),
                   "res/conditions/scaleHeight24.png",
                   "res/conditions/scaleHeight.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .AddParameter("relationalOperator", GD_T("Sign of the test"))
        .AddParameter("expression", GD_T("Value to test"))
        .MarkAsAdvanced()
        .SetFunctionName("GetHeight").SetManipulatedType("number").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddAction("SetMapSize",
                   _("Resize the tilemap"),
                   _("Change the size of the tilemap (number of tiles)."),
                   _("Resize the tilemap to _PARAM1_x_PARAM2_ tiles"),
                   _("Size"),
                   "CppPlatform/Extensions/TileMapIcon24.png",
                   "res/TileMapIcon16.png")
        .AddParameter("objectList", _("Tile Map Object"), "TileMap", false)
        .AddParameter("expression", _("Width (tiles count)"))
        .AddParameter("expression", _("Height (tiles count)"))
        .MarkAsSimple()
        .SetFunctionName("SetMapSize").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    extension.AddCondition("SingleTileCollision",
                   _("Collision with one tile"),
                   _("Test if an object collides a specific tile."),
                   GD_T("_PARAM4_ is in collision with the tile at _PARAM2_;_PARAM3_ (layer _PARAM1_) of _PARAM0_"),
                   _("Collisions"),
                   "res/conditions/collision24.png",
                   "res/conditions/collision.png")
        .AddParameter("objectList", GD_T("Tile Map Object"), "TileMap", false)
        .AddParameter("expression", GD_T("Tile layer (0: Back, 1: Middle, 2: Top)"))
        .AddParameter("expression", GD_T("Tile column"))
        .AddParameter("expression", GD_T("Tile row"))
        .AddParameter("objectList", GD_T("Object"))
        .AddCodeOnlyParameter("conditionInverted", "")
        .MarkAsSimple()
        .SetFunctionName("SingleTileCollision").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");


    obj.AddExpression("TileWidth", GD_T("Tile width"), GD_T("Tile width"), GD_T("Tiles"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .SetFunctionName("GetTileWidth").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddExpression("TileHeight", GD_T("Tile height"), GD_T("Tile height"), GD_T("Tiles"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .SetFunctionName("GetTileHeight").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddExpression("MapWidth", GD_T("Map width (tiles)"), GD_T("Map width"), GD_T("Map"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .SetFunctionName("GetMapWidth").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddExpression("MapHeight", GD_T("Map height (tiles)"), GD_T("Map height"), GD_T("Map"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .SetFunctionName("GetMapHeight").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");



    obj.AddExpression("GetTile", GD_T("Get the Tile (id)"), GD_T("Get the Tile (id)"), GD_T("Map"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .AddParameter("expression", GD_T("Layer"), "", false)
        .AddParameter("expression", GD_T("Column"), "", false)
        .AddParameter("expression", GD_T("Row"), "", false)
        .SetFunctionName("GetTile").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");


    obj.AddAction("SetTile",
                   _("Change a tile"),
                   _("Change a tile at a specific cell."),
                   GD_T("Set tile #_PARAM4_ at the cell _PARAM2_;_PARAM3_ (layer: _PARAM1_) in _PARAM0_"),
                   _("Tiles"),
                   "CppPlatform/Extensions/TileMapIcon24.png",
                   "res/TileMapIcon16.png")
        .AddParameter("objectList", GD_T("Tile Map Object"), "TileMap", false)
        .AddParameter("expression", GD_T("Tile layer (0: Back, 1: Middle, 2: Top)"))
        .AddParameter("expression", GD_T("Tile column"))
        .AddParameter("expression", GD_T("Tile row"))
        .AddParameter("expression", GD_T("New tile Id (-1 to delete the tile)"))
        .MarkAsSimple()
        .SetFunctionName("SetTile").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");



    obj.AddExpression("GetColumnAt", GD_T("Get tile column from X coordinates"), GD_T("Get tile column from X coordinates"), GD_T("Map"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .AddParameter("expression", GD_T("X"), "", false)
        .SetFunctionName("GetColumnAt").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddExpression("GetRowAt", GD_T("Get tile row from Y coordinates"), GD_T("Get tile row from Y coordinates"), GD_T("Map"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .AddParameter("expression", GD_T("Y"), "", false)
        .SetFunctionName("GetRowAt").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");



    obj.AddStrExpression("SaveTiles", GD_T("Save the tile map"), GD_T("Save the tile map content in a string"), GD_T("Saving"), "res/TileMapIcon16.png")
        .AddParameter("object", GD_T("Object"), "TileMap", false)
        .SetFunctionName("SaveAsString").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    obj.AddAction("LoadTiles",
                   _("Load the tiles from a string"),
                   _("Load the tiles from a string."),
                   GD_T("Load the tiles of _PARAM0_ from _PARAM1_"),
                   _("Loading"),
                   "CppPlatform/Extensions/TileMapIcon24.png",
                   "res/TileMapIcon16.png")
        .AddParameter("objectList", GD_T("Tile Map Object"), "TileMap", false)
        .AddParameter("string", GD_T("The string representing the tiles"))
        .MarkAsSimple()
        .SetFunctionName("LoadFromString").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");



    obj.AddAction("ChangeTexture",
                   _("Change the tileset texture"),
                   _("Change the tileset texture."),
                   GD_T("Change the tileset texture of _PARAM0_ to _PARAM1_"),
                   _("Tileset"),
                   "CppPlatform/Extensions/TileMapIcon24.png",
                   "res/TileMapIcon16.png")
        .AddParameter("objectList", GD_T("Tile Map Object"), "TileMap", false)
        .AddParameter("string", GD_T("The new texture name"))
        .AddCodeOnlyParameter("currentScene", "")
        .MarkAsSimple()
        .SetFunctionName("ChangeTexture").SetIncludeFile("TileMapObject/RuntimeTileMapObject.h");

    #endif
}

/**
 * \brief This class declares information about the extension.
 */
class Extension : public ExtensionBase
{
public:

    /**
     * Constructor of an extension declares everything the extension contains: objects, actions, conditions and expressions.
     */
    Extension()
    {
        DeclareTileMapObjectExtension(*this);
        AddRuntimeObject(GetObjectMetadata("TileMapObject::TileMap"),
            "RuntimeTileMapObject", CreateRuntimeTileMapObject);

        GD_COMPLETE_EXTENSION_COMPILATION_INFORMATION();
    };
};

#if !defined(EMSCRIPTEN)
/**
 * Used by GDevelop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" ExtensionBase * GD_EXTENSION_API CreateGDExtension() {
    return new Extension;
}
#endif
