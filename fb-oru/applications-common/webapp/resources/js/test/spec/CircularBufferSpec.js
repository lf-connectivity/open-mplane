describe("CircularBuffer", function() {
  var buffer;
  const BUFFSIZE = 10 ;

  beforeEach(function() {
    buffer = new CircularBuffer(BUFFSIZE);
  });

  it("should initialise empty", function() {
    expect(buffer.empty()).toBe(true);
    expect(buffer.size()).toEqual(0);
    expect(buffer.get(0)).toBeNull();
  });

  describe("add entries", function() {

	    it("should fill up normally", function() {

	    	for (var i=0; i < BUFFSIZE; ++i)
	    	{
		    	buffer.push(i) ;
		        expect(buffer.empty()).not.toBe(true);
		        expect(buffer.size()).toEqual(i+1);
		        expect(buffer.get(0)).not.toBeNull();
		        expect(buffer.get(i)).toEqual(i);
	    	}

	    	// bounds check
	        expect(buffer.get(BUFFSIZE)).toBeNull();
	    });

	    it("should wrap", function() {

	    	// fill
	    	for (var i=0; i < BUFFSIZE; ++i)
	    	{
		    	buffer.push(i) ;
	    	}
	        expect(buffer.size()).toEqual(BUFFSIZE);
	    	buffer.push(BUFFSIZE) ;
	        expect(buffer.size()).toEqual(BUFFSIZE);

	    	// index 0 should now point at 1
	        expect(buffer.get(0)).toEqual(1);

	    	buffer.push(BUFFSIZE+1) ;

	    	// index 0 should now point at 2
	        expect(buffer.get(0)).toEqual(2);

	        for (var i=0; i < BUFFSIZE; ++i)
	        {
		        expect(buffer.get(i)).toEqual(2+i);
	        	console.log(i+'='+buffer.get(i));
	        }

	    });

	    it("should be resetable", function() {

	        buffer.clear() ;
	        expect(buffer.empty()).toBe(true);
	        expect(buffer.size()).toEqual(0);
	        expect(buffer.get(0)).toBeNull();

	    });

	    it("has a next() access method", function() {

	    	// fill
	    	for (var i=0; i < BUFFSIZE; ++i)
	    	{
		    	buffer.push(i) ;
	    	}

	        // next should start at first index and wrap around
	        for (var loop=1; loop <= 3; ++loop )
	        {
		        for (var i=0; i < BUFFSIZE; ++i)
		    	{
			        expect(buffer.next()).toEqual(i);
		    	}
	        }


	    });

	    it("can reset the next pointer", function() {

	    	// fill
	    	for (var i=0; i < BUFFSIZE; ++i)
	    	{
		    	buffer.push(i) ;
	    	}

	    	// step into next a few times to misalign
	    	buffer.next() ;
	    	buffer.next() ;
	    	buffer.next() ;
	    	expect(buffer.next()).not.toEqual(0);

	    	// now reset the pointer
	    	buffer.reset() ;

	        // next should NOW start at first index and wrap around
	        for (var loop=1; loop <= 3; ++loop )
	        {
		        for (var i=0; i < BUFFSIZE; ++i)
		    	{
			        expect(buffer.next()).toEqual(i);
		    	}
	        }


	    });

  });


});
