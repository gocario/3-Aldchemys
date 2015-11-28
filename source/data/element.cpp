#include "data/element.hpp"

const char* elementNames[] =
{
	"None",

	"Water", // 1
	"Fire", // 2
	"Earth", // 3
	"Air", // 4
	"Steam", // 5
	"Lava", // 6
	"Pressure", // 7
	"Volcano", // 8
	"Sea", // 9
	"Ocean", // 10
	"Energy", // 11
	"Mud", // 12
	"Rain", // 13
	"Dust", // 14
	"Cloud", // 15
	"Storm", // 16
	"Geyser", // 17
	"Isle", // 18
	"Earthquake", // 19
	"Wind", // 20
	"Eruption", // 21
	"Sky", // 22
	"Hurricane", // 23
	"Plant", // 24
	"Gunpowder", // 25
	"Explosion", // 26
	"Stone", // 27
	"Sand", // 28
	"Ash", // 29
	"Coal", // 30
	"Diamond", // 31
	"Glass", // 32
	"Hourglass", // 33
	"Aquarium", // 34
	"Greenhouse", // 35
	"Metal", // 36
	"Rust", // 37
	"Boiler", // 38
	"Bullet", // 39
	"Steel", // 40
	"Time", // 41
	"Tree", // 42
	"Swamp", // 43
	"Life", // 44
	"Plankton", // 45
	"Bird", // 46
	"Phoenix", // 47
	"Human", // 48
	"Egg", // 49
	"Clay", // 50
	"Golem", // 51
	"Pottery", // 52
	"Tool", // 53
	"Steam engine", // 54
	"Blade", // 55
	"Wood", // 56
	"Axe", // 57
	"Forest", // 58
	"Love", // 59
	"Lumberjack", // 60
	"Train", // 61
	"Steamboat", // 62
	"Campfire", // 63
	"Hard roe", // 64
	"Omelette", // 65
	"Caviar", // 66
	"Turtle", // 67
	"Fish", // 68
	"Lizard", // 69
	"Field", // 70
	"Farmer", // 71
	"House", // 72
	"Livestock", // 73
	"Chicken", // 74
	"Grass", // 75
	"Cow", // 76
	"Milk", // 77
	"Cheese", // 78
	"Moon", // 79
	"Tobacco", // 80
	"Pipe", // 81
	"Wheel", // 82
	"Bicycle", // 83
	"Wheat", // 84
	"Flour", // 85
	"Dough", // 86
	"Bread", // 87
	"Fruit", // 88
	"Pie", // 89
	"Meat", // 90
	"Sandwich", // 91
	"Smoke", // 92
	"Ham", // 93
	"Gun", // 94
	"Corpse", // 95
	"Zombie", // 96
	"Coffin", // 97
	"Grave", // 98
	"Graveyard", // 99
	"Boat", // 100
	"Desert", // 101
	"Cactus", // 102
	"Seaweed", // 103
	"Dragon", // 104
	"Cyclist", // 105
	"Fireman", // 106
	"Beach", // 107
	"Sun", // 108
	"Palm", // 109
	"Rainbow", // 110
	"Tsunami", // 111
	"Blood", // 112
	"Sailboat", // 113
	"Electricity", // 114
	"Light bulb", // 115
	"Christmas tree", // 116
	"Clock", // 117
	"Frankenstein", // 118
	"Wire", // 119
	"Chainsaw", // 120
	"Electrician", // 121
	"Light", // 122
	"Electric eel", // 123
	"Sunflower", // 124
	"Oil", // 125
	"Day", // 126
	"Night", // 127
	"Solar cell", // 128
	"Eclipse", // 129
	"Wave", // 130
	"Tide", // 131
	"Fireplace", // 132
	"Sundial", // 133
	"Double rainbow!", // 134
	"Scythe", // 135
	"Gravestone", // 136
	"Twilight", // 137
	"Flute", // 138
	"Water pipe", // 139
	"Wild animal", // 140
	"Snake", // 141
	"Sickness", // 142
	"Cold", // 143
	"Snow", // 144
	"Seasickness", // 145
	"Snowman", // 146
	"Toast", // 147
	"Ice", // 148
	"Sword", // 149
	"Penguin", // 150
	"Windmill", // 151
	"Acid rain", // 152
	"Airplane", // 153
	"Algae", // 154
	"Allergy", // 155
	"Alligator", // 156
	"Warrior", // 157
	"Angel", // 158
	"Antarctica", // 159
	"Archipelago", // 160
	"Armor", // 161
	"Astronaut", // 162
	"Atmosphere", // 163
	"Atomic bomb", // 164
	"Pig", // 165
	"Bacteria", // 166
	"Barn", // 167
	"Bayonet", // 168
	"Beaver", // 169
	"Birdhouse", // 170
	"Blizzard", // 171
	"Brick", // 172
	"Owl", // 173
	"Butcher", // 174
	"Car", // 175
	"Charcoal", // 176
	"Star", // 177
	"Knight", // 178
	"Cuckoo", // 179
	"Dinosaur", // 180
	"Dog", // 181
	"Duck", // 182
	"Dune", // 183
	"Engineer", // 184
	"Glasses", // 185
	"Family", // 186
	"Fruit tree", // 187
	"Orchard", // 188
	"Fireworks", // 189
	"Flood", // 190
	"Fog", // 191
	"Garden", // 192
	"Grenade", // 193
	"Hail", // 194
	"Hay", // 195
	"Hero", // 196
	"Horizon", // 197
	"Horse", // 198
	"Hospital", // 199
	"Ice cream", // 200
	"Mountain", // 201
	"Glacier", // 202
	"Alcohol", // 203
	"Nerd", // 204
	"Cart", // 205
	"Wagon", // 206
	"Doctor", // 207
	"Paper", // 208
	"Newspaper", // 209
	"Salt", // 210
	"Vampire", // 211
	"Sunglasses", // 212
	"Igloo", // 213
	"Sandstorm", // 214
	"Oasis", // 215
	"Robot", // 216
	"Sushi", // 217
	"Treehouse", // 218
	"Unicorn", // 219
	"Bacon", // 220
	"Cigarette", // 221
	"Pilot", // 222
	"Seahorse", // 223
	"Fossil", // 224
	"Ring", // 225
	"Pegasus", // 226
	"Shark", // 227
	"Space", // 228
	"Yogurt", // 229
	"Computer", // 230
	"Mouse", // 231
	"Baker", // 232
	"Pencil", // 233
	"Starfish", // 234
	"Wine", // 235
	"Telescope", // 236
	"Pizza", // 237
	"Cat", // 238
	"Sound", // 239
	"Lightsaber", // 240
	"Jedi", // 241
	"Wolf", // 242
	"Werewolf", // 243
	"Grim reaper", // 244
	"Sailor", // 245
	"Camel", // 246
	"Wall", // 247
	"Planet", // 248
	"Rocket", // 249
	"Swordfish", // 250
	"Drunk", // 251
	"Music", // 252
	"Smog", // 253
	"Beer", // 254
	"Seagull", // 255
	"Juice", // 256
	"Village", // 257
	"Scissors", // 258
	"Story", // 259
	"Letter", // 260
	"Coconut", // 261
	"Coconut milk", // 262
	"Sugar", // 263
	"Bat", // 264
	"Squirrel", // 265
	"River", // 266
	"Cookie", // 267
	"Iceberg", // 268
	"Vulture", // 269
	"Bone", // 270
	"Skittles", // 271
	"Cotton candy", // 272
	"Frozen yogurt", // 273
	"Swedish fish", // 274
	"Ring pop", // 275
	"Nerds", // 276
	"Popsicle", // 277
	"Peeps", // 278
	"Pop rocks", // 279
	"Sweethearts", // 280
	"Pokki", // 281
	"Castle", // 282
	"Centaur", // 283
	"Nest", // 284
	"Lion", // 285
	"Doghouse", // 286
	"Skyscraper", // 287
	"Dynamite", // 288
	"Goat", // 289
	"Cereal", // 290
	"Black hole", // 291
	"ELEMENT 292", // 292
	"Starburst", // 293
	"Juicy fruit", // 294
	"Caramel", // 295
	"Goldfish", // 296
	"Astronaut ice cream", // 297
	"Milky way", // 298
	"Guiness float", // 299
	"Caramel apple", // 300
	"Lighthouse", // 301
	"Surfer", // 302
	"Monkey", // 303
	"Idea", // 304
	"Galaxy", // 305
	"Lamp", // 306
	"Mirror", // 307
	"Meteoroid", // 308
	"Meteor", // 309
	"Platypus", // 310
	"Pirate", // 311
	"Lava lamp", // 312
	"Hamburger", // 313
	"Email", // 314
	"Prism", // 315
	"Sandpaper", // 316
	"Kite", // 317
	"Origami", // 318
	"Darth vader", // 319
	"Statue", // 320
	"Willy wonka", // 321
	"Chocolate", // 322
	"Mounds", // 323
	"Caramelo", // 324
	"Twix", // 325
	"Cadbury eggs", // 326
	"Chocolate milk", // 327
	"Cookie dough", // 328
	"Red vines", // 329
	"Fun dip", // 330
	"City", // 331
	"Eagle", // 332
	"Watch", // 333
	"Ambulance", // 334
	"Manatee", // 335
	"Ski goggles", // 336
	"Swim goggles", // 337
	"Cyborg", // 338
	"Mermaid", // 339
	"Sheep", // 340
	"Alien", // 341
	"Book", // 342
	"Batman", // 343
	"Dam", // 344
	"Internet", // 345
	"Motorcycle", // 346
	"Avalanche", // 347
	"Leather", // 348
	"Wizard", // 349
	"Faun", // 350
	"Gold", // 351
	"Moss", // 352
	"Egg timer", // 353
	"Butter", // 354
	"Oxygen", // 355
	"Pyramid", // 356
	"Sand castle", // 357
	"Yoda", // 358
	"Umbrella", // 359
	"Pond", // 360
	"Wool", // 361
	"Scarecrow", // 362
	"Carbon dioxide", // 363
	"Monarch", // 364
	"Bridge", // 365
	"Broom", // 366
	"Leaf", // 367
	"Fridge", // 368
	"Printer", // 369
	"Scorpion", // 370
	"Santa", // 371
	"Reindeer", // 372
	"Sledge", // 373
	"Candy cane", // 374
	"Christmas stocking", // 375
	"Chimney", // 376
	"Sweater", // 377
	"Gift", // 378
	"Snowball", // 379
	"Snowboard", // 380
	"Armadillo", // 381
	"Pigeon", // 382
	"Seaplane", // 383
	"Narwhal", // 384
	"Piranha", // 385
	"Titanic", // 386
	"Obsidian", // 387
	"Mummy", // 388
	"Money", // 389
	"Flying fish", // 390
	"Tank", // 391
	"Solar system", // 392
	"Paper airplane", // 393
	"Banana", // 394
	"Sandstone", // 395
	"Parrot", // 396
	"Dry ice", // 397
	"Flashlight", // 398
	"Dew", // 399
	"Trojan horse", // 400
	"Catnip", // 401
	"Scalpel", // 402
	"Skateboard", // 403
	"Alarm clock", // 404
	"Water gun", // 405
	"Wind turbine", // 406
	"Piggy bank", // 407
	"Sloth", // 408
	"Marshmallows", // 409
	"Seal", // 410
	"Helicopter", // 411
	"Tea", // 412
	"Picnic", // 413
	"Peacock", // 414
	"Rose", // 415
	"Flower", // 416
	"Hummingbird", // 417
	"Chameleon", // 418
	"Fox", // 419
	"Wild boar", // 420
	"Firetruck", // 421
	"Medusa", // 422
	"Flying squirrel", // 423
	"Fence", // 424
	"Electric car", // 425
	"Ostrich", // 426
	"Milk shake", // 427
	"Map", // 428
	"Lawn mower", // 429
	"Mousetrap", // 430
	"Cotton", // 431
	"Thread", // 432
	"Fabric", // 433
	"Bank", // 434
	"Excalibur", // 435
	"Popsicle", // 436
	"Woodpecker", // 437
	"Wand", // 438
	"Pirate ship", // 439
	"Constellation", // 440
	"Computer mouse", // 441
	"Pasta", // 442
	"Shuriken", // 443
	"Ninja", // 444
	"Saddle", // 445
	"Sheet music", // 446
	"Donut", // 447
	"Fishing rod", // 448
	"Lemonade", // 449
	"Mayonnaise", // 450
	"Confetti", // 451
	"Witch", // 452
	"Skeleton", // 453
	"Spider", // 454
	"Web", // 455
	"Ghost", // 456
	"Vegetable", // 457
	"Pumpkin", // 458
	"Crystal ball", // 459
	"Jack-o'-lantern", // 460
	"Bee", // 461
	"Butterfly", // 462
	"Beehive", // 463
	"Honey", // 464
	"Wax", // 465
	"Candle", // 466
	"Water lily", // 467
	"Hippo", // 468
	"Petroleum", // 469
	"Pinocchio", // 470
	"Wrapping paper", // 471
	"Minotaur", // 472
	"Vase", // 473
	"Space station", // 474
	"Soap", // 475
	"Fountain", // 476
	"Needle", // 477
	"Drum", // 478
	"Batter", // 479
	"Snowmobile", // 480
	"Rat", // 481
	"Sphinx", // 482
	"Jam", // 483
	"Cheeseburger", // 484
	"Crow", // 485
	"Taser", // 486
	"Cannon", // 487
	"Blender", // 488
	"Bulletproof vest", // 489
	"Pitchfork", // 490
	"Ufo", // 491
	"Cake", // 492
	"Bbq", // 493
	"Swimmer", // 494
	"Angler", // 495
	"Farm", // 496
	"Ruins", // 497
	"Steak", // 498
	"Spaceship", // 499
	"Godzilla", // 500
	"Horseshoe", // 501
	"Soda", // 502
	"Tractor", // 503
	"Frog", // 504
	"Mailman", // 505
	"Bandage", // 506
	"Log cabin", // 507
	"Bus", // 508
	"Alpaca", // 509
	"Rope", // 510
	"Puddle", // 511
	"Grilled cheese", // 512
	"Pterodactyl", // 513
	"Snow globe", // 514
	"Flamethrower", // 515
	"Waterfall", // 516
	"Ozone", // 517
	"Ant", // 518
	"Paint", // 519
	"Treasure map", // 520
	"Treasure", // 521
	"Hammer", // 522
	"Mountain range", // 523
	"Family tree", // 524
	"Rv", // 525
	"Mold", // 526
	"Bakery", // 527
	"Ice cream truck", // 528
	"Gardener", // 529
	"Super nova", // 530
	"Doge", // 531
	"The one ring", // 532
	"Keyboard cat", // 533
	"Ninja turtle", // 534
	"Gingerbread man", // 535
	"Gingerbread house", // 536
	"Safety glasses", // 537
	"Hay bale", // 538
	"Harp", // 539
	"Fortune cookie", // 540
	"Chicken wing", // 541
	"Recipe", // 542
	"French fries", // 543
	"Ruler", // 544
	"Chicken soup", // 545
	"Iced tea", // 546
	"Tyrannosaurus rex", // 547
	"Lake", // 548
	"Duckling", // 549
	"Toucan", // 550
	"Optical fiber", // 551
	"Stethoscope", // 552
	"Mac and cheese", // 553
	"Nessie", // 554
	"Banana bread", // 555
	"Drone", // 556
	"Jerky", // 557
	"Fairy tale", // 558
	"Ivy", // 559
	"Hamster", // 560
	"Mountain goat", // 561
	"Carrot", // 562
	"Penicillin", // 563
	"Vacuum cleaner", // 564
	"Yeti", // 565
	"Aurora", // 566
	"Bonsai tree", // 567
	"Fire extinguisher", // 568
	"Gnome", // 569
	"Granite", // 570
	"Hedge", // 571
	"Microscope", // 572
	"Mars", // 573
	"Roomba", // 574
	"Smoothie", // 575
	"Tardis", // 576
	"The doctor", // 577
	"Steel wool", // 578
	"Crayon", // 579
	"Tunnel", // 580
	"Quicksand", // 581
	"Parachute", // 582
	"Husky", // 583
	"Roller coaster", // 584
	"Pencil sharpener", // 585
	"Sewing machine", // 586
	"Don quixote", // 587
	
	"Count",
};
