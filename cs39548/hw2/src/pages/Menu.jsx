import { useState, useEffect, useRef } from 'react';
import { useCart } from '../components/Cart';
import menu1 from '../assets/menu1.jpg';
import menu2 from '../assets/menu2.jpg';
import menu3 from '../assets/menu3.jpg';
import menu4 from '../assets/menu4.jpg';
import menu5 from '../assets/menu5.jpg';
import menu6 from '../assets/menu6.jpg';

const Menu = () => {
    const { addToCart } = useCart();
    const [currentImageIndex, setCurrentImageIndex] = useState(0);
    const [quantities, setQuantities] = useState({});
    const sliderRef = useRef(null);

    const images = [menu1, menu2, menu3, menu4, menu5, menu6];

    const menuItems = [
        {
            name: "Classic Burger",
            description: "Juicy beef patty, lettuce, tomato, onion, pickles, and house sauce on a toasted bun.",
            price: 8.99
        },
        {
            name: "Cheese Lover's Burger",
            description: "Beef patty topped with cheddar, Swiss, and American cheese, lettuce, and tomato.",
            price: 9.99
        },
        {
            name: "Veggie Delight",
            description: "Grilled veggie patty, avocado, lettuce, tomato, and vegan mayo on a wheat bun.",
            price: 8.49
        },
        {
            name: "Bacon BBQ Burger",
            description: "Beef patty, crispy bacon, cheddar cheese, onion rings, and smoky BBQ sauce.",
            price: 10.49
        },
        {
            name: "Chicken Sandwich",
            description: "Grilled chicken breast, lettuce, tomato, pickles, and honey mustard sauce.",
            price: 8.99
        },
        {
            name: "Fries Basket",
            description: "Crispy golden fries served with ketchup and house-made aioli.",
            price: 3.99
        }
    ];


    const goToSlide = (index) => {
        setCurrentImageIndex(index);
    };

    const goToPrevious = () => {
        setCurrentImageIndex(
            currentImageIndex === 0 ? images.length - 1 : currentImageIndex - 1
        );
    };

    const goToNext = () => {
        setCurrentImageIndex(
            currentImageIndex === images.length - 1 ? 0 : currentImageIndex + 1
        );
    };

    const getQuantity = (itemName) => {
        return quantities[itemName] || 1;
    };

    const increaseQuantity = (itemName) => {
        setQuantities(prev => ({
            ...prev,
            [itemName]: (prev[itemName] || 1) + 1
        }));
    };

    const decreaseQuantity = (itemName) => {
        setQuantities(prev => ({
            ...prev,
            [itemName]: Math.max(1, (prev[itemName] || 1) - 1)
        }));
    };

    const handleAddToCart = (item) => {
        const quantity = getQuantity(item.name);
        for (let i = 0; i < quantity; i++) {
            addToCart({ name: item.name, price: item.price });
        }
        setQuantities(prev => ({
            ...prev,
            [item.name]: 1
        }));
        alert(`${quantity} x ${item.name} added to cart!`);
    };

    return (
        <section className="max-w-3xl mx-auto mt-10 px-4">
            <h2 className="text-3xl font-bold mb-6 text-center text-white">Our Menu</h2>

            <div className="menu-container overflow-x-auto">
                <table className="min-w-full bg-white rounded-lg shadow-md">
                    <thead>
                        <tr className="bg-red-800 text-white">
                            <th className="py-3 px-4 text-left">Food</th>
                            <th className="py-3 px-4 text-left">Description</th>
                            <th className="py-3 px-4 text-left">Price</th>
                            <th className="py-3 px-4 text-center">Quantity</th>
                            <th className="py-3 px-4 text-left"></th>
                        </tr>
                    </thead>
                    <tbody>
                        {menuItems.map((item, index) => (
                            <tr key={index} className={index % 2 === 1 ? "border-b bg-gray-50" : "border-b"}>
                                <td className="py-3 px-4 font-semibold">{item.name}</td>
                                <td className="py-3 px-4">{item.description}</td>
                                <td className="py-3 px-4">${item.price}</td>
                                <td className="py-3 px-4">
                                    <div className="flex items-center justify-center gap-2">
                                        <button 
                                            className="bg-gray-500 hover:bg-gray-700 text-white w-4 h-8 rounded-full flex items-center justify-center text-lg font-bold"
                                            onClick={() => decreaseQuantity(item.name)}
                                        >
                                            -
                                        </button>
                                        <span className="font-semibold text-lg min-w-[1rem] text-center">
                                            {getQuantity(item.name)}
                                        </span>
                                        <button 
                                            className="bg-gray-500 hover:bg-gray-700 text-white w-4 h-8 rounded-full flex items-center justify-center text-lg font-bold"
                                            onClick={() => increaseQuantity(item.name)}
                                        >
                                            +
                                        </button>
                                    </div>
                                </td>
                                <td className="py-3 px-4">
                                    <button 
                                        className="bg-yellow-400 hover:bg-yellow-500 text-red-900 font-bold py-1 px-3 rounded"
                                        onClick={() => handleAddToCart(item)}
                                    >
                                        Add
                                    </button>
                                </td>
                            </tr>
                        ))}
                    </tbody>
                </table>
            </div>
            <div className="my-8" />
            <div className="slider-container relative h-100 mb-8 rounded-lg overflow-hidden shadow-lg">
                <div 
                    ref={sliderRef}
                    className="flex transition-transform duration-300 ease-in-out"
                    style={{ transform: `translateX(-${currentImageIndex * 100}%)` }}
                >
                    {images.map((image, index) => (
                        <div key={index} className="w-full flex-shrink-0">
                            <img 
                                src={image} 
                                alt={`Menu item ${index + 1}`}
                                className="w-full h-64 object-cover"
                            />
                        </div>
                    ))}
                </div>

                <button 
                    onClick={goToPrevious}
                    className="absolute left-2 top-1/2 transform -translate-y-1/2 bg-black bg-opacity-50 hover:bg-opacity-75 text-white p-2 rounded-full h-32 transition-all duration-200"
                    aria-label="Previous image"
                >
                    &#8249;
                </button>
                <button 
                    onClick={goToNext}
                    className="absolute right-2 top-1/2 transform -translate-y-1/2 bg-black bg-opacity-50 hover:bg-opacity-75 text-white p-2 rounded-full h-32 transition-all duration-200"
                    aria-label="Next image"
                >
                    &#8250;
                </button>

                {/* Dots Indicator */}
                <div className="absolute bottom-4 left-1/2 transform -translate-x-1/2 flex space-x-2">
                    {images.map((_, index) => (
                        <button
                            key={index}
                            onClick={() => goToSlide(index)}
                            className={`w-3 h-3 rounded-full transition-all duration-200 ${
                                index === currentImageIndex 
                                    ? 'bg-white' 
                                    : 'bg-yellow-400 bg-opacity-50 hover:bg-opacity-75'
                            }`}
                            aria-label={`Go to slide ${index + 1}`}
                        />
                    ))}
                </div>
            </div>
        </section>
    );
};

export default Menu;
