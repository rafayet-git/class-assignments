import { useState } from 'react';

const Contact = () => {
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    message: ''
  });

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    alert('Thank you for the message! Into the shredder it goes!');
    setFormData({ name: '', email: '', message: '' });
  };

  return (
    <div>
      <section className="max-w-xl mx-auto mt-12 bg-white rounded-lg shadow-lg p-8">
        <h2 className="text-3xl font-bold mb-6 text-center text-red-900">Contact Us</h2>
        <form onSubmit={handleSubmit} className="flex flex-col gap-6">
          <div>
            <label htmlFor="name" className="block text-sm font-semibold mb-2">Name</label>
            <input 
              type="text" 
              id="name" 
              name="name" 
              value={formData.name}
              onChange={handleChange}
              required 
              className="w-full border border-gray-300 rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-red-400"
            />
          </div>
          <div>
            <label htmlFor="email" className="block text-sm font-semibold mb-2">Email</label>
            <input 
              type="email" 
              id="email" 
              name="email" 
              value={formData.email}
              onChange={handleChange}
              required 
              className="w-full border border-gray-300 rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-red-400"
            />
          </div>
          <div>
            <label htmlFor="message" className="block text-sm font-semibold mb-2">Message</label>
            <textarea 
              id="message" 
              name="message" 
              rows="5" 
              value={formData.message}
              onChange={handleChange}
              required 
              className="w-full border border-gray-300 rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-red-400"
            />
          </div>
          <button 
            type="submit" 
            className="bg-red-900 text-white font-semibold py-2 px-6 rounded hover:bg-red-700 transition"
          >
            Send Message
          </button>
        </form>
      </section>
      
      <section className="max-w-xl mx-auto mt-8 bg-white rounded-lg shadow-lg p-8">
        <h3 className="text-xl font-bold mb-4 text-red-900">Our Location</h3>
        <div className="w-full h-64 rounded overflow-hidden">
          <iframe
            src="https://www.google.com/maps?q=610+W+6th+Ave,+Anchorage,+AK+99501&output=embed"
            width="100%"
            height="100%"
            style={{ border: 0 }}
            allowFullScreen=""
            loading="lazy"
            referrerPolicy="no-referrer-when-downgrade"
            title="Google Maps Location"
          />
        </div>
      </section>
    </div>
  );
};

export default Contact;
